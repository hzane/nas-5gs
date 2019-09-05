#pragma once
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
int dissect_mico_ind(dissector d, context* ctx);
int dissect_full_name_network(dissector d, context* ctx);
int dissect_short_name_network(dissector d, context* ctx);
int dissect_local_time_zone(dissector d, context* ctx);
int dissect_op_def_acc_cat_def(dissector d, context* ctx);
int dissect_sms_ind(dissector d, context* ctx);
int dissect_t3502_gprs_timer_2(dissector d, context* ctx);
int dissect_sec_algo(dissector d, context* ctx);
int dissect_replayed_ue_sec_cap(dissector d, context* ctx);
int dissect_imeisv_req(dissector d, context* ctx);
int dissect_selected_eps_sec_algo(dissector d, context* ctx);
int dissect_a_sec_info(dissector d, context* ctx);
int dissect_reported_s1_ue_sec_cap(dissector d, context* ctx);
int dissect_mm_service_type(dissector d, context* ctx);
int dissect_uplink_data_status(dissector d, context* ctx);
int dissect_allowed_pdu_ses_status(dissector d, context* ctx);
int dissect_pdu_ses_id(dissector d, context* ctx);
int dissect_additional_inf(dissector d, context* ctx);
int dissect_pld_cont_type(dissector d, context* ctx); // 9.11.3.40
int dissect_pld_cont(dissector d, context* ctx);      // 9.11.3.39
int dissect_old_pdu_ses_id(dissector d, context* ctx);
int dissect_req_type(dissector d, context* ctx);

int dissect_last_v_tai(dissector d, context* ctx); //  9.11.3.8
int dissect_s1_ue_net_cap(dissector d, context* ctx);
int dissect_ul_data_status(dissector d, context* ctx);

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

/* 9.11.3.54    UE security capability*/
int dissect_use_sec_cap(dissector d, context* ctx);

int dissect_n3gpp_nw_provided_policies(dissector d, context* ctx);

int dissect_pdu_ses_react_res_err_c(dissector d, context*);

int dissect_sor_trans_cont(dissector d, context* ctx);

int dissect_access_type(dissector d, context*);/*  9.11.3.11    Access type */

int dissect_registration_req(dissector d, context* ctx);
int dissect_registration_accept(dissector d, context* ctx);
int dissect_registration_complete(dissector d, context* ctx);
int dissect_registration_rej(dissector d, context* ctx);
int dissect_reg_req_ue_orig(dissector d, context* ctx);
int dissect_registration_req_ue_term(dissector d, context* ctx);
int dissect_service_req(dissector d, context* ctx);
int dissect_service_rej(dissector d, context* ctx);
int dissect_service_acc(dissector d, context* ctx);

int dissect_conf_upd_cmd(dissector d, context* ctx);
int dissect_conf_update_comp(dissector d, context* ctx);
int authentication_req(dissector d, context* ctx);
int authentication_resp(dissector d, context* ctx);
int authentication_rej(dissector d, context* ctx);
int authentication_failure(dissector d, context* ctx);
int authentication_result(dissector d, context* ctx);
int dissect_id_req(dissector d, context* ctx);
int dissect_id_resp(dissector d, context* ctx);
int dissect_sec_mode_cmd(dissector d, context* ctx);
int dissect_sec_mode_comp(dissector d, context* ctx);
int dissect_sec_mode_rej(dissector d, context* ctx);

int dissect_mm_status(dissector d, context* ctx);
int dissect_notification(dissector d, context* ctx);
int dissect_notification_resp(dissector d, context* ctx);
int dissect_ul_nas_transp(dissector d, context* ctx);
int dissect_dl_nas_transp(dissector d, context* ctx);

int dissect_allowed_nssai(dissector d, context* ctx);
int dissect_ta_id_list(dissector d, context* ctx);

//  9.11.3.46    Rejected NSSAI
int dissect_rejected_nssai(dissector d, context* ctx);

int dissect_configured_nssai(dissector d, context* ctx);

int dissect_pdu_ses_react_res(dissector d, context* ctx = nullptr);

int dissect_pdu_ses_status(dissector d, context* ctx = nullptr); /* 9.11.3.44*/
int dissect_mm_cause(dissector d, context* ctx);                 // 5GMM cause   9.11.3.2
int dissect_drx_param(dissector d, context* ctx);

int dissect_ladn_inf(dissector d, context* ctx); /*  9.11.3.30    LADN information */
int dissect_mobile_id(dissector d, context* ctx);

//  9.11.3.36    Network slicing indication
int dissect_nw_slicing_ind(dissector d, context* ctx);
int dissect_nas_ksi(dissector d, context* ctx);
int dissect_nas_msg_cont(dissector d, context* ctx = nullptr);

int dissect_abba(dissector d, context* ctx);
int dissect_requested_nssai(dissector d, context* ctx);
int dissect_eps_bearer_context_status(dissector d, context* ctx);

int dissect_mobile_id_noid(dissector d, context* ctx);    // 0, no identity
int dissect_mobile_id_suci(dissector d, context* ctx);    // 1, SUCI
int dissect_mobile_id_5gguti(dissector d, context* ctx);  // 2, 5G-GUTI
int dissect_mobile_id_imei(dissector d, context* ctx);    // 3, IMEI
int dissect_mobile_id_5gstmsi(dissector d, context* ctx); // 4, 5G-S-TMSI
int dissect_mobile_id_imeisv(dissector d, context* ctx);  // 5, IMEISV
int dissect_mobile_id_mac(dissector d, context* ctx);     // 6, MAC address
int dissect_5gs_id_type(dissector d, context* ctx);
int dissect_nw_feat_sup(dissector d, context* ctx);
/*  5GS registration result    9.11.3.6    M    LV 2 */
int dissect_reg_res(dissector d, context* ctx = nullptr);

int dissect_reg_req_type(dissector d, context* ctx);
//  5GMM capability  9.11.3.1
int dissect_mm_cap(dissector d, context* ctx);

int dissect_updp(dissector d, context* ctx);
} // namespace mm
