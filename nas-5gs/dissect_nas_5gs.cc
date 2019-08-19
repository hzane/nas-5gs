#include "core.hh"
#include "dissect_nas_5gs.hh"
#include "dissect_sm_msg.hh"
#include "dissect_mm_msg.hh"

extern const field_meta* hf_nas_5gs_epd;
extern const field_meta* hf_nas_5gs_spare_half_octet;
extern const field_meta* hf_nas_5gs_security_header_type;
extern const field_meta* hf_nas_5gs_msg_auth_code;
extern const field_meta* hf_nas_5gs_seq_no;
extern const field_meta* hf_nas_5gs_pdu_session_id;
extern const field_meta* hf_nas_5gs_proc_trans_id;
extern const field_meta* hf_nas_5gs_msg_elems;
extern const field_meta* hf_nas_5gs_sm_msg_type;

int dissect_nas_5gs(packet_info* pinfo,
                    proto_node*  tree,
                    tvbuff*      buf,
                    int          offset,
                    int          len,
                    context*     ctx) {
    auto item = tree->add_subtree(pinfo, buf, offset, 0, nas_5gs_module.name);

    auto epd = buf->get_uint8(offset);
    if (epd == TGPP_PD::SM5G) { // always plain format
        return dissect_nas_5gs_plain(pinfo, tree, buf, offset, len, ctx);
    }

    /* Security header type associated with a spare half octet;
    /* or PDU session identity           octet 2 */
    /* Determine if it's a plain 5GS NAS Message or not */
    auto sec_type = buf->get_uint8(offset + 1);

    if (sec_type == 0) { // NAS_5GS_PLAIN_NAS_MSG;
        return dissect_nas_5gs_plain(pinfo, tree, buf, offset, len, ctx);
    }
    /* Security protected NAS 5GS message*/
    auto sub_tree =
        item->add_subtree(pinfo, buf, offset, 7, "Security protected NAS 5GS message");

    /* Extended protocol discriminator  octet 1 */
    sub_tree->add_item(pinfo, buf, offset, 1, hf_nas_5gs_epd, enc::be);
    offset++;

    /* Security header type associated with a spare half octet    octet 2 */
    sub_tree->add_item(pinfo, buf, offset, 1, hf_nas_5gs_spare_half_octet, enc::be);
    sub_tree->add_item(pinfo, buf, offset, 1, hf_nas_5gs_security_header_type, enc::be);
    offset++;

    /* Message authentication code octet 3 - 6 */
    sub_tree->add_item(pinfo, buf, offset, 4, hf_nas_5gs_msg_auth_code, enc::be);
    offset += 4;

    /* Sequence number    octet 7 */
    sub_tree->add_item(pinfo, buf, offset, 1, hf_nas_5gs_seq_no, enc::be);
    offset++;

    // TODO: decrypt the body
    item->add_subtree(pinfo, buf, offset, -1, "Encrypted data");

    return buf->reported_length;
}

static int dissect_nas_5gs_plain(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      tvb,
                                 int          offset,
                                 int          length,
                                 context*     ctx) {
    /* Plain NAS 5GS Message */
    auto sub_tree =
        tree->add_subtree(pinfo, tvb, offset, -1, "Plain NAS 5GS Message");

    /* Extended protocol discriminator  octet 1 */
    auto epd = tvb->get_uint8(offset);
    sub_tree->add_item(pinfo, tvb, offset, 1, hf_nas_5gs_epd, enc::be);
    offset++;

    /* Security header type associated with a spare half octet; or
     * PDU session identity octet 2
     */
    if (epd == TGPP_PD::MM5G){
        /* 9.5  Spare half octet
         * Bits 5 to 8 of the second octet of every 5GMM message contains the spare
         * half octet which is filled with spare bits set to zero.
         */
        sub_tree->add_item(pinfo, tvb, offset, 1, hf_nas_5gs_spare_half_octet, enc::be);
        sub_tree->add_item(pinfo,
                           tvb,
                           offset,
                           1,
                           hf_nas_5gs_security_header_type,
                           enc::be);
    }
    else if (epd == TGPP_PD::SM5G){
        /* 9.4  PDU session identity
         * Bits 1 to 8 of the second octet of every 5GSM message contain the PDU
         * session identity IE. The PDU session identity and its use to identify a
         * message flow are defined in 3GPP TS 24.007
         */
        sub_tree->add_item(pinfo, tvb, offset, 1, hf_nas_5gs_pdu_session_id, enc::be);
        offset++;
        /* 9.6  Procedure transaction identity
         * Bits 1 to 8 of the third octet of every 5GSM message contain the procedure
         * transaction identity. The procedure transaction identity and its use are
         * defined in 3GPP TS 24.007
         * XXX Only 5GSM ?
         */
        sub_tree->add_item(pinfo, tvb, offset, 1, hf_nas_5gs_proc_trans_id, enc::be);
    }
    else{
        sub_tree->add_expert(pinfo, tvb, offset, -1, "Not a NAS 5GS PD %u", epd);
        return 0;
    }

    offset++; // skip the second oct
    if (epd == TGPP_PD::MM5G) {
        dissect_mm_msg(pinfo, sub_tree, tvb, offset, tvb->remain(offset), ctx);
    } else if (epd == TGPP_PD::SM5G) {
        dissect_sm_msg(pinfo, sub_tree, tvb, offset, tvb->remain(offset), ctx);
    }

    return tvb->reported_length;
}

// begin with offset == 2, message type
static int dissect_sm_msg(packet_info* pinfo,
                          proto_node*  tree,
                          tvbuff*      tvb,
                          int          offset,
                          int          length,
                          context*     ctx) {
    auto len = tvb->reported_length;

    /* Message type IE*/
    uint8_t iei = tvb->get_uint8(offset); // offset == 2

    auto meta  = find_dissector(iei, sm::msgs);
    if (meta == nullptr ){
        add_unknown(pinfo, tree, tvb, offset, length, iei, ctx); // ignore return
        return len;
    }

    // Add NAS message name
    tree->add_item(pinfo, tvb, offset, 1, hf_nas_5gs_sm_msg_type, enc::be);
    offset++;

    if (meta->fnc){
        (meta->fnc)(pinfo, tree, tvb, offset, len - offset, ctx);
    } else {
        add_generic_msg_elem_body(pinfo, tree, tvb, offset, len - offset, ctx);
    }
    return len;
}

static int dissect_mm_msg(packet_info* pinfo,
                                   proto_node*  tree,
                                   tvbuff*      tvb,
                                   int          offset,
                                   int          length,
                                   context*     ctx) {
    auto len = tvb->reported_length;

    /* Message type IE*/
    uint8_t iei = tvb->get_uint8(offset); // offset == 2

    auto meta = find_dissector(iei, mm::msgs);
    if (meta == nullptr) {
        add_unknown(pinfo, tree, tvb, offset, length, iei, ctx); // ignore return
        return len;
    }

    // Add NAS message name
    tree->add_item(pinfo, tvb, offset, 1, hf_nas_5gs_sm_msg_type, enc::be);
    offset++;

    if (meta->fnc) {
        (meta->fnc)(pinfo, tree, tvb, offset, len - offset, ctx);
    } else {
        add_generic_msg_elem_body(pinfo, tree, tvb, offset, len - offset, ctx);
    }
    return len;
}
