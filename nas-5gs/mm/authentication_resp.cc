#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_authentication_resp{
extern const element_meta auth_resp_par;
}
/*
 *8.2.2    Authentication response
 */
int mm::authentication_resp(dissector d, context* ctx) {
    use_context uc(ctx, "authentication-response");

    using namespace mm_authentication_resp;

    /* 2D    Authentication response parameter    Authentication response
     * parameter 9.11.3.15    O    TLV    6-18 */
    // ELEM_OPT_TLV(0x2d, NAS_PDU_TYPE_EMM, DE_EMM_AUTH_RESP_PAR, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &auth_resp_par, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /* 78 EAP message    EAP message     9.10.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
namespace mm_authentication_resp {
int                       dissect_auth_resp_par(dissector d, context* ctx);
extern const element_meta auth_resp_par = {
    0x2d,
    "Authentication response parameter",
    dissect_auth_resp_par,
};

} // namespace mm_authentication_resp
