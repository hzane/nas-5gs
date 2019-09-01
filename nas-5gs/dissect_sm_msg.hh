#pragma once
#include "core.hh"

/* 5GS session management messages */
namespace sm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int pdu_ses_est_req(dissector d, context* ctx);
int pdu_ses_est_acc(dissector d, context* ctx);
int pdu_ses_est_rej(dissector d, context* ctx);
int pdu_ses_auth_cmd(dissector d, context* ctx);
int pdu_ses_auth_comp(dissector d, context* ctx);
int pdu_ses_mod_req(dissector d, context* ctx);
int pdu_ses_mod_rej(dissector d, context* ctx);
int pdu_ses_mod_cmd(dissector d, context* ctx);
int pdu_ses_mod_comp(dissector d, context* ctx);
int pdu_ses_auth_res(dissector d, context* ctx);
int pdu_ses_mod_com_rej(dissector d, context* ctx);
int pdu_ses_rel_req(dissector d, context* ctx);
int pdu_ses_rel_rej(dissector d, context* ctx);
int pdu_ses_rel_cmd(dissector d, context* ctx);
int pdu_ses_rel_comp(dissector d, context* ctx);
int sm_status(dissector d, context* ctx);

int dissect_sm_cause(dissector d, context* ctx);
int dissect_ext_pco(dissector d, context* ctx);
int dissect_eap_msg(dissector d, context* ctx);
int dissect_authorized_qos_rules(dissector d, context* ctx);
int dissect_qos_rules(dissector d, context* ctx);
int dissect_mapped_eps_b_cont(dissector d, context* ctx);

int dissect_sm_cap(dissector d, context* ctx);
int dissect_max_num_sup_kpt_flt(dissector d, context* ctx);
int dissect_ses_ambr(dissector d, context* ctx);
int dissect_always_on_pdu_ses_ind(dissector d, context* ctx);
int dissect_int_prot_max_data_rate(dissector d, context* ctx);
int dissect_allowed_ssc_mode(dissector d, context* ctx);
int dissect_sm_s_nssai(dissector d, context* ctx);

//*      9.11.4.16    SSC mode
int dissect_ssc_mode(dissector d, context* ctx);

extern const value_string sm_unit_for_session_ambr_values[];

extern const true_false_string tfs_allowed_not_allowed;
extern const true_false_string tfs_nas_5gs_sm_dqr ;
extern const true_false_string tfs_supported_not_supported;

extern const message_meta msgs[];

extern const element_meta sm_cause;
extern const element_meta ext_pco;
extern const element_meta eap_msg;
extern const element_meta authorized_qos_rules;
extern const element_meta mapped_eps_b_cont;
extern const element_meta backoff_gprs_timer3;
extern const element_meta sm_cap;
extern const element_meta max_num_sup_kpt_flt ;
extern const element_meta ses_ambr ;
extern const element_meta rq_gprs_timer ;
extern const element_meta always_on_pdu_ses_ind ;
extern const element_meta allowed_ssc_mode;

extern const field_meta hf_sm_ses_ambr_dl_unit ;
extern const field_meta hf_sm_ses_ambr_ul_unit ;
extern const field_meta hf_sm_ses_ambr_dl;
extern const field_meta hf_sm_ses_ambr_ul;

extern const value_string sm_cause_values[];
extern const field_meta   hf_sm_cause;

// *     9.11.4.13    QoS rules

extern const value_string rule_operation_code_values[] ;
extern const value_string sm_pf_type_values[] ;
extern const value_string sm_pkt_flt_dir_values[] ;
extern const value_string rule_param_cont[] ;
extern const field_meta hf_sm_dqr;
extern const field_meta hf_sm_rop ;
extern const field_meta hf_sm_nof_pkt_filters;
extern const field_meta hf_sm_qfi ;
extern const field_meta hf_sm_qos_rule_id;
extern const field_meta hf_sm_length;
extern const field_meta hf_sm_pkt_flt_id;
extern const field_meta hf_sm_pkt_flt_dir;
extern const field_meta hf_sm_pf_len;
extern const field_meta hf_sm_pf_type;
extern const field_meta hf_pdu_addr_ipv4;
extern const field_meta hf_sm_qos_rule_precedence;

/*   9.11.4.8 Mapped EPS bearer contexts  */
extern const value_string sm_mapd_eps_b_cont_opt_code_values[] ;
extern const value_string sm_mapd_eps_b_cont_deb_values[] ;
extern const value_string sm_mapd_eps_b_cont_e_values[] ;
extern const value_string sm_mapd_eps_b_cont_E_Modify_values[] ;
extern const value_string sm_mapd_eps_b_cont_param_id_values[] ;

extern const field_meta hf_sm_mapd_eps_b_cont_opt_code ;
extern const field_meta hf_sm_mapd_eps_b_cont_deb ;
extern const field_meta hf_sm_mapd_eps_b_cont_e ;
extern const field_meta hf_sm_mapd_eps_b_cont_num_eps_parms ;
extern const field_meta hf_sm_mapd_eps_b_cont_e_mod ;
extern const field_meta hf_sm_mapd_eps_b_cont_id ;
extern const field_meta hf_sm_mapd_eps_b_cont_num_eps_param_id;
extern const field_meta hf_sm_mapd_eps_b_cont_eps_param_cont ;
extern const field_meta hf_sm_rqos_b0 ;

//  *      9.11.4.14    Session-AMBR
extern const value_string sm_unit_for_session_ambr_values[] ;

// * 9.11.4.7 Integrity protection maximum data rate
extern const value_string sm_int_prot_max_data_rate_values[] ;

extern const field_meta hf_sm_int_prot_max_data_rate_ul;
extern const field_meta hf_sm_int_prot_max_data_rate_dl;

extern const field_meta hf_sm_all_ssc_mode_b2 ;
extern const field_meta hf_sm_all_ssc_mode_b1 ;
extern const field_meta hf_sm_all_ssc_mode_b0 ;

/* 9.11.4.16    SSC mode */

extern const value_string sc_mode_values[] ;
extern const field_meta hf_sm_sc_mode;
} // namespace sm
