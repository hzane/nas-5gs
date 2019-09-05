#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"
#include "pdu_ses.hh"

using namespace nas;
using namespace sm;

/* 8.3.1 PDU session establishment request */
int sm::dissect_pdu_ses_est_req(dissector d, context* ctx) {    
    use_context uc(ctx, "pdu-session-establishment-request", d, 0);

    /* Direction: UE to network */
    down_link(d.pinfo);    

    /*Integrity protection maximum data rate 9.11.4.7    M    V    2*/
    // ELEM_MAND_V(, DE_NAS_5GS_SM_INT_PROT_MAX_DATA_RTE,);
    auto consumed = dissect_elem_v(nullptr, &int_prot_max_data_rate, d, ctx);
    d.step(consumed);

    /*9-    PDU session type     9.11.4.11    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0x90, , DE_NAS_5GS_SM_PDU_SESSION_TYPE,);
    consumed = dissect_opt_elem_tv_short(nullptr, &pdu_ses_type, d, ctx);
    d.step(consumed);

    /*A-    SSC mode  9.11.4.16    O    TV    1*/
    // ELEM_OPT_TV_SHORT(0xa0, , DE_NAS_5GS_SM_SSC_MODE, );
    consumed = dissect_opt_elem_tv_short(nullptr, &ssc_mode, d, ctx);
    d.step(consumed);

    /*28    5GSM capability  9.11.4.1    O    TLV    3-15 */
    // ELEM_OPT_TLV(0x28, , DE_NAS_5GS_SM_5GSM_CAP, );
    consumed = dissect_opt_elem_tlv(nullptr, &sm_cap, d, ctx);
    d.step(consumed);

    /*55    Maximum number of supported packet filter 9.11.4.9    O    TV    3*/
    // ELEM_OPT_TV(0x55, , DE_NAS_5GS_SM_MAX_NUM_SUP_PKT_FLT, );
    consumed = dissect_opt_elem_tv(nullptr, &max_num_sup_kpt_flt, d, ctx);
    d.step(consumed);

    // B-	Always-on PDU session requested    9.11.4.4 O TV 1
    // ELEM_OPT_TV_SHORT(0xB0, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_REQ, );
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_req, d, ctx);
    d.step(consumed);

    /*39   SM PDU DN request container 9.11.4.15    O     * TLV    3-255 */
    consumed = dissect_opt_elem_tlv(nullptr, &sm_pdu_dn_req_cont, d, ctx);

    /*7B    Extended protocol configuration options  9.11.4.2    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, , DE_ESM_EXT_PCO, );
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);    

    return uc.length;
}
namespace sm {




} // namespace sm_pdu_ses_est
