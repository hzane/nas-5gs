#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

namespace sm_pdu_ses_est {
extern const element_meta int_prot_max_date_rate;
extern const element_meta pdu_ses_type;
extern const element_meta ssc_mode;
} // namespace sm_pdu_ses_est

using namespace nas;
using namespace sm;

/*
 * 8.3.1 PDU session establishment request
 */
int sm::pdu_ses_est_req(dissector d, context* ctx) {
    use_context uc(ctx, "pdu-session-establishment-request");

    using namespace sm_pdu_ses_est;

    /* Direction: UE to network */
    d.pinfo->dir = pi_dir::ul;

    /*Integrity protection maximum data rate    Integrity protection maximum data
     * rate 9.11.4.7    M    V    2*/
    // ELEM_MAND_V(, DE_NAS_5GS_SM_INT_PROT_MAX_DATA_RTE,);
    auto consumed = dissect_elem_v(nullptr, &int_prot_max_date_rate, d, ctx);
    d.step(consumed);

    /*9-    PDU session type    PDU session type     9.11.4.5    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_SM_PDU_SESSION_TYPE,);
    consumed = dissect_opt_elem_tv_short(nullptr, &pdu_ses_type, d, ctx);
    d.step(consumed);

    /*A-    SSC mode    SSC mode     9.11.4.9    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xa0, , DE_NAS_5GS_SM_SSC_MODE, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &ssc_mode, d, ctx);
    d.step(consumed);

    /*28    5GSM capability    5GSM capability     9.11.4.10    O    TLV    3-15 */
    // ELEM_OPT_TLV(0x28, , DE_NAS_5GS_SM_5GSM_CAP, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &sm_cap, d, ctx);
    d.step(consumed);

    /*55    Maximum number of supported packet filter    Maximum number of suuported
     * packet filter   9.11.4.9    O    TV    3*/
    // ELEM_OPT_TV(0x55, , DE_NAS_5GS_SM_MAX_NUM_SUP_PKT_FLT, NULL);
    consumed = dissect_opt_elem_tv(nullptr, &max_num_sup_kpt_flt, d, ctx);
    d.step(consumed);

    /*39    SM PDU DN request container    SM PDU DN request container 9.11.4.15    O
     * TLV    3-255 */

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options     9.11.4.2    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    // extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    d.extraneous_data_check(0);

    return d.tvb->length;
}
namespace sm_pdu_ses_est {
extern const element_meta int_prot_max_date_rate = {
    0xff,
    "Integrity protection maximum data rate",
    dissect_int_prot_max_data_rate,
};

extern const element_meta ssc_mode = {
    0xa0,
    "SSC mode",
    dissect_ssc_mode,
};
} // namespace sm_pdu_ses_est
