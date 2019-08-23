#include "dissect_sm_msg.hh"
#include "ts24007.hh"

/* 8.3 5GS session management messages */

#if 0
/*
 * 8.3.6 PDU session authentication result
 */
int sm::pdu_ses_auth_res(dissector d, context* ctx) {

    /* Direction: network to UE */
    pinfo->link_dir = P2P_DIR_DL;
    d.pinfo->dir = pi_dir::dl;

    /*EAP message    EAP message 9.11.2.2    M    LV-E    6-1502 */
    ELEM_MAND_LV_E(NAS_5GS_PDU_TYPE_COMMON,
                   DE_NAS_5GS_CMN_EAP_MESSAGE,
                   NULL,
                   ei_nas_5gs_missing_mandatory_elemen);
    consumed = dissect_elem_lv_e(nullptr, &eap_msg, d);
    d.offset += consumed;
    d.length -= consumed;

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d);
    d.offset += consumed;
    d.length -= consumed;

    EXTRANEOUS_DATA_CHECK(curr_len, 0, pinfo, &ei_nas_5gs_extraneous_data);
}
#endif

int sm::dissect_sm_cause(dissector d, context* ctx) { return 0; }

int sm::dissect_ext_pco(dissector d, context* ctx) { return 0; }

int sm::dissect_eap_msg(dissector d, context* ctx) { return 0; }

int sm::dissect_authorized_qos_rules(dissector d, context* ctx) { return 0; }

int sm::dissect_mapped_eps_b_cont(dissector d, context* ctx) { return 0; }

int sm::dissect_backoff_gprs_timer3(dissector d, context* ctx) { return 0; }

int sm::dissect_sm_cap(dissector d, context* ctx) { return 0; }

int sm::dissect_max_num_sup_kpt_flt(dissector d, context* ctx) { return 0; }

int sm::dissect_ses_ambr(dissector d, context* ctx) { return 0; }

int sm::dissect_rq_gprs_timer(dissector d, context* ctx) { return 0; }

int sm::dissect_always_on_pdu_ses_ind(dissector d, context* ctx) { return 0; }
