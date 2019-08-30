#include "dissect_nas5g.hh"
#include "core.hh"
#include "dissect_mm_msg.hh"
#include "dissect_sm_msg.hh"
#include "ts24007.hh"

using namespace nas;

int dissect_nas5g(dissector d, context* ctx) {
    auto item = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, nas_5gs_module.name);

    auto epd = d.tvb->uint8(d.offset);
    if (epd == EPD::SM5G) { // always plain format
        return dissect_nas5g_plain(d, ctx);
    }

    /* Security header type associated with a spare half octet; */
    /* or PDU session identity           octet 2 */
    /* Determine if it's a plain 5GS NAS Message or not */
    auto sec_type = d.tvb->uint8(d.offset + 1);

    if (sec_type == 0) { // NAS_5GS_PLAIN_NAS_MSG;
        return dissect_nas5g_plain(d, ctx);
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

    return d.tvb->length;
}

int dissect_nas5g_plain(dissector d, context* ctx) {
    /* Plain NAS 5GS Message */
    auto subtree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Plain NAS 5GS Message");

    /* Extended protocol discriminator  octet 1 */
    auto epd = d.tvb->uint8(d.offset);
    subtree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_epd, enc::be);
    d.offset++;

    /* Security header type associated with a spare half octet; or
     * PDU session identity octet 2
     */
    if (epd == EPD::MM5G){
        /* 9.5  Spare half octet
         * Bits 5 to 8 of the second octet of every 5GMM message contains the spare
         * half octet which is filled with spare bits set to zero.
         */
        subtree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
        subtree->add_item(d.pinfo,
                           d.tvb,
                           d.offset,
                           1, hf_sec_header_type,
                           enc::be);
    }
    else if (epd == EPD::SM5G){
        /* 9.4  PDU session identity
         * Bits 1 to 8 of the second octet of every 5GSM message contain the PDU
         * session identity IE. The PDU session identity and its use to identify a
         * message flow are defined in 3GPP TS 24.007
         */
        subtree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_pdu_session_id, enc::be);
        d.offset++;

        /* 9.6  Procedure transaction identity
         * Bits 1 to 8 of the third octet of every 5GSM message contain the procedure
         * transaction identity. The procedure transaction identity and its use are
         * defined in 3GPP TS 24.007
         * XXX Only 5GSM ?
         */
        subtree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_proc_trans_id, enc::be);
    }
    else{
        subtree->add_expert(d.pinfo, d.tvb, d.offset, -1, "Not a NAS 5GS PD %u", epd);
        return 0;
    }

    d.offset++; // skip the second oct
    d.tree = subtree;
    d.length = d.tvb->remain(d.offset);

    if (epd == EPD::MM5G) {
        dissect_mm_msg(d, ctx);
    } else {
        dissect_sm_msg(d, ctx);
    }

    return d.tvb->length;
}

// begin with offset == 2, message type
static int dissect_sm_msg(dissector d, context* ctx) {
    auto len = d.tvb->length;

    /* Message type IE*/
    uint8_t iei = d.tvb->uint8(d.offset); // offset == 2

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
    auto len = d.tvb->length;

    /* Message type IE*/
    uint8_t iei = d.tvb->uint8(d.offset); // offset == 2

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

/*
 * 9.11.2.1A    DNN
 */
int nas::dissect_dnn(dissector d, context* ctx) {
    auto len = d.length;
    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */
    string str(d.safe_ptr(), d.safe_ptr() + d.safe_length(-1));
    size_t i = 0;
    while (i < str.size()) {
        auto next = str[i];
        str[i]    = '.';
        i         = i + next + 1;
    }
    /* Highlight bytes including the first length byte */
    auto item = d.add_item(len, &hf_dnn, enc::none);
    item->set_string(str);
    // d.tree->add_subtree(d.pinfo, d.tvb, d.offset, d.length, str.c_str());
    d.step(len);

    d.extraneous_data_check(0);
    return len;
}

/* 9.10.2.8    S-NSSAI */
int nas::dissect_s_nssai(dissector d, context* ctx) {
    /* SST    octet 3
     * This field contains the 8 bit SST value. The coding of the SST value part is
     * defined in 3GPP TS 23.003
     */
    d.add_item(1, &hf_sst, enc::be);
    d.step(1);
    if (d.length <= 0) {
        return 1;
    }

    /* SD    octet 4 - octet 6* */
    d.add_item(3, &hf_sd, enc::be);
    d.step(3);
    if (d.length <= 0) {
        return 4;
    }

    /* Mapped configured SST    octet 7* */
    d.add_item(1, &hf_mapped_conf_sst, enc::be);
    d.step(1);
    if (d.length <= 0) {
        return 5;
    }

    /* Mapped configured SD    octet 8 - octet 10* */
    d.add_item(3, &hf_mapped_conf_ssd, enc::be);
    d.step(3);

    d.extraneous_data_check(0);
    return 8;
}

const message_meta* find_dissector(uint8_t iei, const message_meta* meta) {
    while (meta->type) {
        if (meta->type == iei) return meta;
        meta++;
    }
    return nullptr;
}
