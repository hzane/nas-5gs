#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"


using namespace nas;

/* 8.2.2    Authentication response */
int mm::authentication_resp(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-response", d, 0);

    /* 2D    Authentication response parameter 9.11.3.17    O    TLV    18 */
    // ELEM_OPT_TLV(0x2d, , DE_EMM_AUTH_RESP_PAR, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &auth_resp_par, d, ctx);
    d.step(consumed);

    /* 78 EAP message    EAP message     9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &cmn::eap_msg, d, ctx);
    d.step(consumed);
    
    return uc.length;
}
