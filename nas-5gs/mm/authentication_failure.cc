#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"


namespace mm_authentication_failure{

extern const element_meta auth_fail_param;
}
/*
 * 8.2.4 Authentication failure
 */
int mm::authentication_failure(dissector d, context* ctx) {
    using namespace mm_authentication_failure;

    /* 5GMM cause   5GMM cause     9.11.3.2  M   V   1 */
    // ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
    //             DE_NAS_5GS_MM_5GMM_CAUSE,
    //             NULL,
    //             ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &mm_cause, d);
    d.offset += consumed;
    d.length -= consumed;

    /* 30    Authentication failure parameter    Authentication failure
     * parameter 9.11.3.14    O    TLV    16 */
    // ELEM_OPT_TLV(0x30, GSM_A_PDU_TYPE_DTAP, DE_AUTH_FAIL_PARAM, NULL);
    auto consumed = dissect_opt_elem_tlv(nullptr, &auth_fail_param, d);
    d.offset += consumed;
    d.length -= consumed;

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
namespace mm_authentication_failure {
int dissect_mm_fail_param(dissector d, context* ctx);

extern const element_meta mm_fail_param = {
    0x30,
    "Authentication failure parameter",
    dissect_mm_fail_param,
};
} // namespace mm_authentication_failure
