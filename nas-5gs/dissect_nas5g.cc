#include "dissect_nas5g.hh"
#include "core.hh"
#include "dissect_mm_msg.hh"
#include "dissect_sm_msg.hh"

using namespace cmn;
using namespace nas;

int dissect_nas5g(dissector d, context* ctx){
    const auto epd = d.uint8();
    if (epd == EPD::SM5G) return dissect_nas5g_plain(d, ctx);

    // Security header type (octet 1)
    auto security_type = d.tvb->uint8(d.offset + 1) & 0x0fu;
    if (security_type == 0) { // Plain 5GS NAS message, not security protected
        return dissect_nas5g_plain(d, ctx);
    }
    return dissect_nas5g_security_protected(d, ctx);
}

int dissect_nas5g_security_protected(dissector d, context* ctx){
    const auto        subtree = d.add_item(7, "Security protected NAS 5GS message");
    use_tree    ut(d, subtree);
    const use_context uc(ctx, subtree->name.c_str(), d, 0);

    /* 9.2 Extended protocol discriminator  octet 1 */
    auto i = d.add_item(1, hf_epd, enc::be);
    d.step(1);
    unused(i);

    /* 9.3 Security header type associated    1/2 */
    i = d.add_item(1, hf_sec_header_type, enc::be);
    // 9.5 Spare half octet 1/2
    i = d.add_item(1, hf_spare_half_octet, enc::be);
    d.step(1);

    /* 9.8 Message authentication code octet 3 - 6 */
    store_msg_auth_code(ctx, d.uint32());
    i = d.add_item(4, hf_msg_auth_code, enc::be);
    d.step(4);

    /* 9.10 Sequence number    octet 7 */
    i = d.add_item(1, hf_seq_no, enc::be);
    d.step(1);

    // TODO: decrypt the body
    // This should work when the NAS ciphering algorithm is NULL (128-EEA0)
    const auto consumed = dissect_nas5g_plain(d, ctx);
    d.step(consumed);

    return uc.length;
}

int dissect_nas5g_plain(dissector d, context* ctx) {
    /* Plain NAS 5GS Message */
    const use_context uc(ctx, "Plain NAS 5GS Message", d, 0);

    /* Extended protocol discriminator  octet 1 */
    const auto epd = d.uint8();

    if (epd == EPD::MM5G) {
        return dissect_mm_msg(d, ctx);
    }
    if (epd == EPD::SM5G) {
        return dissect_sm_msg(d, ctx);
    }
    diag("unknown epd %d\n", epd);
    return d.length;
}

static int dissect_sm_msg(dissector d, context* ctx) {
    const auto        subtree = d.add_item(-1, "5GS Session Management Message");
    use_tree    ut(d, subtree);
    const use_context uc(ctx, subtree->name.c_str(), d, 0);

    /* Extended protocol discriminator  octet 1 */
    auto i = d.add_item(1, hf_epd, enc::be);
    d.step(1);
    unused(i);

    /* PDU session ID	PDU session identity 9.4	M	V	1     */
    i = d.add_item(1, hf_pdu_sess_id, enc::be);
    d.step(1);

    /* PTI	Procedure transaction identity 9.6	M	V	1     */
    i = d.add_item(1, hf_proc_trans_id, enc::be);
    d.step(1);

    /* Message type 9.7	M	V	1*/
    const uint8_t iei = d.uint8(); // offset == 2
    i = d.add_item(1, hf_sm_msg_type, enc::be);
    d.step(1);

    const auto meta  = find_dissector(iei, sm::msgs);
    const auto consumed = (meta && meta->fnc) ? meta->fnc(d, ctx) : 0;
    d.step(consumed);

    return uc.length;
}

static int dissect_mm_msg(dissector d, context* ctx) {
    const auto        subtree = d.add_item(-1, "5GS Mobility Management Message");
    use_tree    ut(d, subtree);
    const use_context uc(ctx, subtree->name.c_str(), d, 0);

    /* Extended protocol discriminator 9.2 octet 1 */
    auto i = d.add_item(1, hf_epd, enc::be);
    d.step(1);
    unused(i);

    /*Security header type 9.3	M	V	1/2 */
    i = d.add_item(1, hf_sec_header_type, enc::be);
    /*Spare half octet	Spare half octet 9.5	M	V	1/2*/
    i = d.add_item(1, hf_spare_half_octet, enc::be);
    d.step(1);

    /* Authentication request message identity	Message type 9.7	M	V	1*/
    const uint8_t iei = d.uint8();
    i = d.add_item(1, hf_mm_msg_type, enc::be);
    d.step(1);

    const auto meta = find_dissector(iei, mm::msgs);
    const auto consumed = (meta && meta->fnc) ? meta->fnc(d, ctx) : 0;
    d.step(consumed);

    return uc.length;
}

