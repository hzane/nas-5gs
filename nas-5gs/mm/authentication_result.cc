#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

using namespace nas;

/*
 * 8.2.3 Authentication result
 */
int mm::authentication_result(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "authentication-result");

    /* ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2
       Spare half octet    Spare half octet 9.5    M    V    1/2  H1 */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);

    // ELEM_MAND_V(DE_NAS_5GS_MM_NAS_KEY_SET_ID, " - ngKSI",);
    auto consumed = dissect_elem_v(nullptr, &nas_ksi, d, ctx);
    d.step(consumed);

    /* EAP message    EAP message     9.11.2.2    M    LV-E    7-1503 */
    consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /* 38    ABBA    ABBA 9.11.3.10    O    TLV    4-n */
    // ELEM_OPT_TLV(0x38, , DE_NAS_5GS_MM_ABBA, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &abba, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}


