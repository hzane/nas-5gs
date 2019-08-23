#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_service_acc {
extern const element_meta pdu_ses_react_res;
extern const element_meta pdu_ses_react_res_error_c;

} // namespace mm_service_acc
/*
 * 8.2.17 Service accept
 */
int mm::service_acc(dissector d, context* ctx) {
    use_context uc(ctx, "service-accept");
    using namespace mm_service_acc;

    /*50    PDU session status    PDU session status     9.11.3.44    O    TLV    4-34*/
    // ELEM_OPT_TLV(0x50, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*26    PDU session reactivation result    PDU session reactivation result 9.11.3.42
     * O    TLV    4-32*/
    // ELEM_OPT_TLV(0x26, NAS_5GS_PDU_TYPE_MM, DE_NAS_5GS_MM_PDU_SES_REACT_RES, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_react_res, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*72    PDU session reactivation result error cause    PDU session reactivation result
     * error cause 9.11.3.43    O    TLV-E    5-515 */
    // ELEM_OPT_TLV_E(
    //    0x72, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pdu_ses_react_res_error_c, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    /*78    EAP message    EAP message     9.11.2.2    O    TLV-E    7-1503*/
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);

    return d.tvb->reported_length;
}

namespace mm_service_acc {
int                       dissect_pdu_ses_react_res(dissector d, context*);
extern const element_meta pdu_ses_react_res = {
    0x26,
    "PDU session reactivation result",
    dissect_pdu_ses_react_res,
};
int                       dissect_pdu_ses_react_res_err_c(dissector d, context*);
extern const element_meta pdu_ses_react_res_error_c = {
    0x72,
    "PDU session reactivation result error cause",
    dissect_pdu_ses_react_res_err_c,
};

int dissect_pdu_ses_react_res(dissector d, context*) { return 0; }

int dissect_pdu_ses_react_res_err_c(dissector d, context*) { return 0; }

} // namespace mm_service_acc
