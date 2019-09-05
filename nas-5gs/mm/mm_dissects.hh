#include "../core.hh"

namespace mm {
int dissect_auth_fail_param(dissector d, context* ctx);
int dissect_auth_parm_rand(dissector d, context* ctx);
int dissect_auth_parm_autn(dissector d, context* ctx);
int dissect_auth_resp_param(dissector d, context* ctx);
int dissect_de_reg_type(dissector d, context* ctx);
int dissect_key_set_id(dissector d, context* ctx);
int dissect_conf_upd_ind(dissector d, context* ctx);
int dissect_guti(dissector d, context* ctx);
int dissect_sal(dissector d, context* ctx);
int dissect_time_zone_time(dissector d, context* ctx);
int dissect_day_saving_time(dissector d, context* ctx);
// int dissect_ladn_ind(dissector d, context* ctx);
int dissect_mico_ind(dissector d, context* ctx);
int dissect_full_name_network(dissector d, context* ctx);
int dissect_short_name_network(dissector d, context* ctx);
int dissect_local_time_zone(dissector d, context* ctx);
int dissect_op_def_acc_cat_def(dissector d, context* ctx);
int dissect_sms_ind(dissector d, context* ctx);
int dissect_auth_fail_param(dissector d, context* ctx);
int dissect_auth_parm_rand(dissector d, context* ctx);
int dissect_auth_parm_autn(dissector d, context* ctx);
int dissect_auth_resp_param(dissector d, context* ctx);
int dissect_de_reg_type(dissector d, context* ctx);
int dissect_key_set_id(dissector d, context* ctx);
int dissect_t3346_gprs_timer2(dissector d, context* ctx);
int dissect_t3502_gprs_timer_2(dissector d, context* ctx);
int dissect_sec_algo(dissector d, context* ctx);
int dissect_replayed_ue_sec_cap(dissector d, context* ctx);
int dissect_imeisv_req(dissector d, context* ctx);
int dissect_selected_eps_sec_algo(dissector d, context* ctx);
int dissect_a_sec_info(dissector d, context* ctx);
int dissect_reported_s1_ue_sec_cap(dissector d, context* ctx);
int dissect_key_set_id(dissector d, context* ctx);
int dissect_mm_service_type(dissector d, context* ctx);
int dissect_uplink_data_status(dissector d, context* ctx);
int dissect_allowed_pdu_ses_status(dissector d, context* ctx);
int dissect_pdu_ses_id(dissector d, context* ctx);
int dissect_additional_inf(dissector d, context* ctx);
int dissect_pld_cont_type(dissector d, context* ctx); // 9.11.3.40
int dissect_pld_cont(dissector d, context* ctx);      // 9.11.3.39
int dissect_pdu_ses_id(dissector d, context* ctx);
int dissect_old_pdu_ses_id(dissector d, context* ctx);
int dissect_req_type(dissector d, context* ctx);

int dissect_last_v_tai(dissector d, context* ctx); //  9.11.3.8
int dissect_s1_ue_net_cap(dissector d, context* ctx);
int dissect_ul_data_status(dissector d, context* ctx);

int dissect_mico_ind(dissector d, context* ctx); //  MICO indication    9.11.3.31

int dissect_ue_status(dissector d, context* ctx ); // 9.11.3.56

// 9.11.3.4
int dissect_aguti_mobile_id(dissector d, context* ctx );

// 9.11.3.13
int dissect_pdu_ses_sts(dissector d, context* ctx );

// 9.11.3.55
int dissect_usage_set(dissector d, context* ctx );

// 9.11.3.2A
int dissect_requested_drx_param(dissector d, context* ctx );

// 9.11.3.24
int dissect_eps_nas_msg_cont(dissector d, context* ctx );

// 9.11.3.29
int dissect_ladn_ind(dissector d, context* ctx );

// 9.11.3.9A 5GS update type
int dissect_update_type(dissector d, context* ctx );

int dissect_nksi_key_set_id(dissector d, context* ctx );

int dissect_pld_cont_type(dissector d, context* ctx );

/* 9.11.3.54    UE security capability*/
int dissect_use_sec_cap(dissector d, context* ctx);

int dissect_n3gpp_nw_provided_policies(dissector d, context* ctx);

int dissect_pdu_ses_react_res_err_c(dissector d, context*);

int dissect_sor_trans_cont(dissector d, context* ctx);

int dissect_access_type(dissector d, context*);/*  9.11.3.11    Access type */

int dissect_de_reg_type(dissector d, context* ctx); // De-registration type   9.11.3.20

int dissect_key_set_id(dissector d, context* ctx); // 5GS mobile identity  9.11.3.4

int dissect_key_set_id(dissector d, context* ctx); // 5GS mobile identity 9.11.3.4

int dissect_auth_resp_param(dissector d, context* ctx); // 9.11.3.17

// 9.11.3.16 Authentication parameter RAND
int dissect_auth_parm_rand(dissector d, context* ctx);
int dissect_auth_parm_autn(dissector d, context* ctx);
int dissect_auth_fail_param(dissector d, context* ctx); // 10.5.3.2.2 in 3GPP TS 24.008

// NAS key set identifier 9.11.3.32
int dissect_key_set_id(dissector d, context* ctx);
} // namespace mm
