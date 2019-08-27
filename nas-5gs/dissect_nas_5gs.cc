#include "core.hh"
#include "dissect_nas_5gs.hh"
#include "dissect_sm_msg.hh"
#include "dissect_mm_msg.hh"
#include "ts24007.hh"

using namespace nas;

extern const field_meta* hf_seq_no;
extern const field_meta* hf_proc_trans_id;

int dissect_nas_5gs(dissector d, context* ctx) {
    auto item = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, nas_5gs_module.name);

    auto epd = d.tvb->get_uint8(d.offset);
    if (epd == TGPP_PD::SM5G) { // always plain format
        return dissect_nas_5gs_plain(d, ctx);
    }

    /* Security header type associated with a spare half octet; */
    /* or PDU session identity           octet 2 */
    /* Determine if it's a plain 5GS NAS Message or not */
    auto sec_type = d.tvb->get_uint8(d.offset + 1);

    if (sec_type == 0) { // NAS_5GS_PLAIN_NAS_MSG;
        return dissect_nas_5gs_plain(d, ctx);
    }
    /* Security protected NAS 5GS message*/
    auto sub_tree =
        item->add_subtree(d.pinfo, d.tvb, d.offset, 7, "Security protected NAS 5GS message");

    /* Extended protocol discriminator  octet 1 */
    sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_epd, enc::be);
    d.offset++;

    /* Security header type associated with a spare half octet    octet 2 */
    sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    sub_tree->add_item(
        d.pinfo, d.tvb, d.offset, 1, hf_sec_header_type, enc::be);
    d.offset++;

    /* Message authentication code octet 3 - 6 */
    sub_tree->add_item(d.pinfo, d.tvb, d.offset, 4, hf_msg_auth_code, enc::be);
    d.offset += 4;

    /* Sequence number    octet 7 */
    sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_seq_no, enc::be);
    d.offset++;

    // TODO: decrypt the body
    item->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Encrypted data");

    return d.tvb->reported_length;
}

int dissect_nas_5gs_plain(dissector d, context* ctx) {
    /* Plain NAS 5GS Message */
    auto sub_tree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Plain NAS 5GS Message");

    /* Extended protocol discriminator  octet 1 */
    auto epd = d.tvb->get_uint8(d.offset);
    sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_epd, enc::be);
    d.offset++;

    /* Security header type associated with a spare half octet; or
     * PDU session identity octet 2
     */
    if (epd == TGPP_PD::MM5G){
        /* 9.5  Spare half octet
         * Bits 5 to 8 of the second octet of every 5GMM message contains the spare
         * half octet which is filled with spare bits set to zero.
         */
        sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
        sub_tree->add_item(d.pinfo,
                           d.tvb,
                           d.offset,
                           1, hf_sec_header_type,
                           enc::be);
    }
    else if (epd == TGPP_PD::SM5G){
        /* 9.4  PDU session identity
         * Bits 1 to 8 of the second octet of every 5GSM message contain the PDU
         * session identity IE. The PDU session identity and its use to identify a
         * message flow are defined in 3GPP TS 24.007
         */
        sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_pdu_session_id, enc::be);
        d.offset++;

        /* 9.6  Procedure transaction identity
         * Bits 1 to 8 of the third octet of every 5GSM message contain the procedure
         * transaction identity. The procedure transaction identity and its use are
         * defined in 3GPP TS 24.007
         * XXX Only 5GSM ?
         */
        sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_proc_trans_id, enc::be);
    }
    else{
        sub_tree->add_expert(d.pinfo, d.tvb, d.offset, -1, "Not a NAS 5GS PD %u", epd);
        return 0;
    }

    d.offset++; // skip the second oct
    d.tree = sub_tree;
    d.length = d.tvb->remain(d.offset);

    if (epd == TGPP_PD::MM5G) {
        dissect_mm_msg(d, ctx);
    } else {
        dissect_sm_msg(d, ctx);
    }

    return d.tvb->reported_length;
}

// begin with offset == 2, message type
static int dissect_sm_msg(dissector d, context* ctx) {
    auto len = d.tvb->reported_length;

    /* Message type IE*/
    uint8_t iei = d.tvb->get_uint8(d.offset); // offset == 2

    auto meta  = find_dissector(iei, sm::msgs);
    if (meta == nullptr ){
        add_unknown(d, iei, ctx); // ignore return
        return len;
    }

    // Add NAS message name
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_sm_msg_type, enc::be);
    d.offset++;

    d.length = d.length - d.offset;
    if (meta->fnc){
        (meta->fnc)(d, ctx);
    } else {
        add_generic_msg_elem_body(d, ctx);
    }
    return len;
}

static int dissect_mm_msg(dissector d, context* ctx) {
    auto len = d.tvb->reported_length;

    /* Message type IE*/
    uint8_t iei = d.tvb->get_uint8(d.offset); // offset == 2

    auto meta = find_dissector(iei, mm::msgs);
    if (meta == nullptr) {
        add_unknown(d, iei, ctx); // ignore return
        return len;
    }

    // Add NAS message name
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_mm_msg_type, enc::be);
    d.offset++;
    d.length = d.length - d.offset;

    if (meta->fnc) {
        (meta->fnc)(d, ctx);
    } else {
        add_generic_msg_elem_body(d, ctx);
    }
    return len;
}

/* 9.10.2.2    EAP message*/
int nas::dissect_eap_msg(dissector d, context* ctx) {
    /* EAP message as specified in IETF RFC 3748 */
    add_generic_msg_elem_body(d, ctx);
    return d.length;
}
