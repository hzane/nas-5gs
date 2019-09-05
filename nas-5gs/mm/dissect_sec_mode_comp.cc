#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

const element_meta imeisv_mobile_id = {
    0x77,
    "5G mobile identity - IMEISV",
    mm::dissect_mobile_id,
    nullptr,
};

/*  8.2.26 Security mode complete */
int mm::dissect_sec_mode_comp(dissector d, context* ctx) {
    const use_context uc(ctx, "security-mode-complete", d, 0);

    /* 77    IMEISV    5G mobile identity 9.11.3.4    O    TLV-E    11 */
    // ELEM_OPT_TLV_E(0x77, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_5GS_MOBILE_ID, NULL);
    auto consumed = dissect_opt_elem_tlv_e(nullptr, &imeisv_mobile_id, d, ctx);
    d.step(consumed);

    /* 71    NAS message container  9.11.3.33    O    TLV-E    4-n  */
    // ELEM_OPT_TLV_E(0x71, , DE_NAS_5GS_MM_NAS_MSG_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &nas_msg_cont, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
