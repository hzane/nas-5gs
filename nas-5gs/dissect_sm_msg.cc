#include "dissect_sm_msg.hh"
#include "ts24007.hh"

/* 8.3 5GS session management messages */
namespace sm {
extern const field_meta* hf_sel_sc_mode;

extern const element_meta sm_cause;
extern const element_meta ext_pco;
extern const element_meta eap_msg;
extern const element_meta authorized_qos_rules; // 3
extern const element_meta mapped_eps_b_cont;    // 3
extern const element_meta backoff_gprs_timer3;  // 3

extern const element_meta sm_cap; // 2
extern const element_meta max_num_sup_kpt_flt; // 2
extern const element_meta ses_ambr; // 2
extern const element_meta rq_gprs_timer;          // 2
extern const element_meta always_on_pdu_ses_ind; // 2
extern const element_meta dnn;                 // 1
extern const element_meta allowed_ssc_mode;    // 1
extern const element_meta always_on_pdu_ses_req; // 1
extern const element_meta int_prot_max_data_rate; // 1
extern const element_meta requested_qos_rules; // 1
extern const element_meta authorized_qos_flow_des; // 1
extern const element_meta int_prot_max_date_rate;  // 1
extern const element_meta pdu_ses_type;            // 1
extern const element_meta ssc_mode;                // 1
extern const element_meta pdu_address;             // 1
extern const element_meta s_nssai;                 // 1
} // namespace sm





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
