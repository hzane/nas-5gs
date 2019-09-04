#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_service_acc {
extern const element_meta pdu_ses_react_res;
extern const element_meta pdu_ses_react_res_error_c;

} // namespace mm_service_acc

using namespace nas;
using namespace mm;

/*  8.2.17 Service accept */
int mm::service_acc(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "service-accept", d);
    using namespace mm_service_acc;

    /*50  PDU session status     9.11.3.44    O    TLV    4-34*/
    // ELEM_OPT_TLV(0x50, , DE_NAS_5GS_MM_PDU_SES_STATUS, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_status, d, ctx);
    d.step(consumed);

    /*26    PDU session reactivation result 9.11.3.42 O    TLV    4-32*/
    // ELEM_OPT_TLV(0x26, , DE_NAS_5GS_MM_PDU_SES_REACT_RES, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &pdu_ses_react_res, d, ctx);
    d.step(consumed);


    /*72 PDU session reactivation result error cause 9.11.3.43    O    TLV-E    5-515 */
    // ELEM_OPT_TLV_E(  0x72, , DE_NAS_5GS_MM_PDU_SES_REACT_RES_ERR_C, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &pdu_ses_react_res_error_c, d, ctx);
    d.step(consumed);


    /*78    EAP message 9.11.2.2    O    TLV-E    7-1503*/
    // ELEM_OPT_TLV_E(0x78, , DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    // XX	T3448 value	GPRS timer 3  9.11.2.4 O TLV 3
    // consumed = dissect_opt_elem_tlv(nullptr, &t3348_gprs_timer3, d, ctx);
    // d.step(consumed);

    d.extraneous_data_check(3);

    return len;
}

namespace mm_service_acc {

int                       dissect_pdu_ses_react_res_err_c(dissector d, context*);
extern const element_meta pdu_ses_react_res_error_c = {
    0x72,
    "PDU session reactivation result error cause",
    dissect_pdu_ses_react_res_err_c,
    nullptr,
};

//  *   9.11.3.43    PDU session reactivation result error cause
int dissect_pdu_ses_react_res_err_c(dissector d, context*) {
    auto len = d.length;
    /*Partial service area list*/
    while (d.length>0) {
        d.add_item(1, hf_pdu_sess_id, enc::be);
        d.step(1);
        d.add_item(1, &hf_mm_cause, enc::be);
        d.step(1);
    }
    return len;
}

} // namespace mm_service_acc
