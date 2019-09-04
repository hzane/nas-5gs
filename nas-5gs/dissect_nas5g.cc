#include "dissect_nas5g.hh"
#include "core.hh"
#include "dissect_mm_msg.hh"
#include "dissect_sm_msg.hh"
#include "ts24007.hh"

using namespace nas;

int dissect_nas5g(dissector d, context* ctx) {
    auto len = d.length;
    // auto epd = d.tvb->uint8(d.offset);
    auto epd = d.uint8();
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
    // auto     item = d.add_item(-1, nas_5gs_module.name);
    // use_tree ut(d, item);

    /* Security protected NAS 5GS message*/

    auto subtree = d.add_item(7, "Security protected NAS 5GS message");
    use_tree    ut(d, subtree);
    use_context uc(ctx, subtree->name.c_str(), d);

    /* Extended protocol discriminator  octet 1 */
    d.add_item(1, hf_epd, enc::be);
    // sub_tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_epd, enc::be);
    d.step(1);

    /* Security header type associated with a spare half octet    octet 2 */
    d.add_item(1, hf_spare_half_octet, enc::be);
    d.add_item(1, hf_sec_header_type, enc::be);
    d.step(1);


    /* Message authentication code octet 3 - 6 */
    d.add_item(4, hf_msg_auth_code, enc::be);
    d.step(4);

    /* Sequence number    octet 7 */
    d.add_item(1, hf_seq_no, enc::be);
    d.step(1);

    // TODO: decrypt the body
    // This should work when the NAS ciphering algorithm is NULL (128-EEA0)
    auto consumed = dissect_nas5g_plain(d, ctx);

    return len;
}

int dissect_nas5g_plain(dissector d, context* ctx) {
    auto len = d.length;
    /* Plain NAS 5GS Message */
    auto subtree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Plain NAS 5GS Message");
    use_tree    ut(d, subtree);
    use_context uc(ctx, subtree->name.c_str(), d);

    /* Extended protocol discriminator  octet 1 */
    auto epd = d.uint8();
    d.add_item(1, hf_epd, enc::be);
    d.step(1);

    /* Security header type associated with a spare half octet; or
     * PDU session identity octet 2
     */
    if (epd == EPD::MM5G){
        /* 9.5  Spare half octet
         * Bits 5 to 8 of the second octet of every 5GMM message contains the spare
         * half octet which is filled with spare bits set to zero.
         */
        d.add_item(1, hf_sec_header_type, enc::be);
        d.add_item(1, hf_spare_half_octet, enc::be);
    }
    else if (epd == EPD::SM5G){
        /* 9.4  PDU session identity
         * Bits 1 to 8 of the second octet of every 5GSM message contain the PDU
         * session identity IE. The PDU session identity and its use to identify a
         * message flow are defined in 3GPP TS 24.007
         */
        d.add_item(1, hf_pdu_sess_id, enc::be);
        d.step(1);

        /* 9.6  Procedure transaction identity
         * Bits 1 to 8 of the third octet of every 5GSM message contain the procedure
         * transaction identity. The procedure transaction identity and its use are
         * defined in 3GPP TS 24.007
         * XXX Only 5GSM ?
         */
        d.add_item(1, hf_proc_trans_id, enc::be);
    }
    else{
        diag("Not a NAS 5GS PD %u\n", epd);
        return 0;
    }
    d.step(1);

    if (epd == EPD::MM5G) {
        dissect_mm_msg(d, ctx);
    } else {
        dissect_sm_msg(d, ctx);
    }

    return len;
}

// begin with offset == 2, message type
static int dissect_sm_msg(dissector d, context* ctx) {
    auto len = d.tvb->length;

    /* Message type IE*/
    uint8_t iei = d.uint8(); // offset == 2
    d.add_item(1, hf_sm_msg_type, enc::be);
    d.step(1);

    auto meta  = find_dissector(iei, sm::msgs);
    if (meta && meta->fnc) meta->fnc(d, ctx);
    // ignore unknown messages
    return len;
}

static int dissect_mm_msg(dissector d, context* ctx) {
    auto len = d.tvb->length;

    /* Message type IE*/
    uint8_t iei = d.uint8(); // offset == 2
    d.add_item(1, hf_mm_msg_type, enc::be);
    d.step(1);

    auto meta = find_dissector(iei, mm::msgs);
    if (meta && meta->fnc) meta->fnc(d, ctx);
    return len;
}

const field_meta hf_eap = {
    "EAP",
    "nas_5gs.eap",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// RFC2284 RFC3748
/* 9.11.2.2    EAP message*/
int nas::dissect_eap_msg(dissector d, context* ctx) {
    /* EAP message as specified in IETF RFC 3748 */
    diag("no dissect %s\n", ctx->path().c_str());
    d.add_item(d.length, &hf_eap, enc::na);
    return d.length;
}

/*  9.11.2.1A    DNN */
// a type 4 information page.348
int nas::dissect_dnn(dissector d, context* ctx) {
    auto len = d.length;
    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */
    auto   str = bstrn_string(d.safe_ptr(), d.safe_length(-1));

    /* Highlight bytes including the first length byte */
    auto item = d.add_item(len, &hf_dnn, enc::be);
    // item->set_string(str);
    d.step(len);

    d.extraneous_data_check(0);
    return len;
}

// 9.11.2.6 Intra N1 mode NAS transparent container page.349
//  a type 4 information element with a length of 9 octets
int dissect_n1_mode_container(dissector d, context* ctx){
    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/

    return d.length;
}

const field_meta hf_n1_to_s1_mode = {
    "N1 mode to S1 mode NAS transparent container",
    "n1_mode_2_s1_mode_container",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};
// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int dissect_n1_to_s1_mode_container(dissector d, context* ctx){
    // a type 3 information element with a length of 2 octets
    // auto seq = d.ntohs();
    d.add_item(2, &hf_n1_to_s1_mode, enc::be);
    return d.length;
}
