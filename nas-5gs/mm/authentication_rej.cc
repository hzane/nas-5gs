#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

using namespace nas;

/* 8.2.5 Authentication reject */
int mm::authentication_rej(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-reject", d, 0);

    /* 78    EAP message  9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    const auto consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
