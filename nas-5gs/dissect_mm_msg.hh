#pragma once
#include "dissect_nas5g.hh"

/* 9.7  Message type */

/* 5GS mobility management messages */
namespace mm {
__declspec(selectany) extern const dissect_fnc_t no_dissect = nullptr;

int registration_req(dissector d, context* ctx);
int registration_accept(dissector d, context* ctx);
int registration_complete(dissector d, context* ctx);
int registration_rej(dissector d, context* ctx);
int dissect_reg_req_ue_orig(dissector d, context* ctx);
int dissect_registration_req_ue_term(dissector d, context* ctx);
int service_req(dissector d, context* ctx);
int service_rej(dissector d, context* ctx);
int service_acc(dissector d, context* ctx);

int conf_upd_cmd(dissector d, context* ctx);
int conf_update_comp(dissector d, context* ctx);
int authentication_req(dissector d, context* ctx);
int authentication_resp(dissector d, context* ctx);
int authentication_rej(dissector d, context* ctx);
int authentication_failure(dissector d, context* ctx);
int authentication_result(dissector d, context* ctx);
int id_req(dissector d, context* ctx);
int id_resp(dissector d, context* ctx);
int sec_mode_cmd(dissector d, context* ctx);
int sec_mode_comp(dissector d, context* ctx);
int sec_mode_rej(dissector d, context* ctx);

int mm_status(dissector d, context* ctx);
int notification(dissector d, context* ctx);
int notification_resp(dissector d, context* ctx);
int ul_nas_transp(dissector d, context* ctx);
int dl_nas_transp(dissector d, context* ctx);

int dissect_allowed_nssai(dissector d, context* ctx);
int dissect_ta_id_list(dissector d, context* ctx);

int dissect_nssai(dissector d, context* ctx);
//  9.11.3.46    Rejected NSSAI
int dissect_rejected_nssai(dissector d, context* ctx);

int dissect_configured_nssai(dissector d, context* ctx);

int dissect_pdu_ses_react_res(dissector d, context* ctx = nullptr);

/* 9.11.3.44    PDU session status */
int dissect_pdu_ses_status(dissector d, context* ctx = nullptr);
int dissect_mm_cause(dissector d, context* ctx);

int dissect_ladn_inf(dissector d, context* ctx);
int dissect_ladn_ind(dissector d, context* ctx);
int dissect_mico_ind(dissector d, context* ctx);
int dissect_sal(dissector d, context* ctx);
int dissect_mobile_id(dissector d, context* ctx);
int dissect_pld_cont(dissector d, context* ctx);
int dissect_pld_cont_type(dissector d, context* ctx);
int dissect_updp(dissector d, context* ctx);

//  9.11.3.36    Network slicing indication
int dissect_nw_slicing_ind(dissector d, context* ctx);
int dissect_nas_ksi(dissector d, context* ctx);
int dissect_nas_msg_cont(dissector d, context* ctx = nullptr);
int dissect_s_nssai(dissector d, context* ctx);

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

extern const message_meta      msgs[];
extern const true_false_string tfs_requested_not_requested;
extern const true_false_string tfs_sal_al_t;
extern const true_false_string tfs_odd_even;
extern const true_false_string tfs_eps_tsc;

extern const element_meta allowed_nssai;
extern const element_meta ta_id_list;
extern const element_meta rej_nssai;
extern const element_meta configured_nssai;
extern const element_meta pdu_ses_react_res;
extern const element_meta pdu_ses_status;
extern const element_meta mobile_id;
extern const field_meta   hf_mm_length;
extern const field_meta   hfm_mm_cause;
extern const field_meta   hf_mm_cause;
extern const field_meta   hf_mm_type_id;
extern const field_meta   hf_mm_sst;
extern const field_meta   hf_sst;

extern const value_string mm_pld_cont_type_values[];
extern const val_string   mm_type_id_values[];
extern const val_string   values_cause[];
extern const val_string   mm_sal_t_li_values[];
extern const val_string   nas_eps_emm_nas_ksi_values[];
extern const val_string   values_pld_cont_type[];

extern const field_meta  hf_tac;
extern const field_meta  hf_tal_num_e;
extern const field_meta  hf_tal_t_li;
extern const field_meta* hf_mm_raai_b0;
extern const field_meta  hf_plt_cont_type;
extern const field_meta  hf_mm_odd_even;
extern const field_meta  hf_pld_cont;
extern const field_meta  hf_pld_cont_type;
extern const field_meta  hfm_nas_eps_tsc;
extern const field_meta* hf_nas_eps_tsc;
extern const field_meta  hf_follow_on_req;

extern const field_meta   hf_abba;
extern const field_meta   hfm_mm_conf_upd_ind_ack_b0;
extern const field_meta   hfm_nas_eps_nas_ksi;
extern const field_meta*  hf_nas_eps_nas_ksi;
extern const element_meta nas_ksi;
extern const element_meta mm_cause;
extern const element_meta nas_msg_cont;
extern const element_meta abba;
extern const element_meta eps_bearer_ctx_status;

extern const true_false_string tfs_supported_not_supported;
extern const true_false_string tfs_nas_5gs_mm_n1_mod;
extern const true_false_string tfs_nas_5gs_mm_s1_mod;
extern const val_string        mm_type_of_enc_algo_vals[];
extern const val_string        mm_type_of_ip_algo_vals[];
extern const val_string        mm_req_type_vals[];
extern const val_string        mm_serv_type_vals[];
extern const val_string        mm_sal_t_li_values[];

extern const field_meta hfm_nas_5gs_mm_conf_upd_ind_red_b1;
extern const field_meta hfm_mm_nas_sec_algo_enc;
extern const field_meta hfm_mm_nas_sec_algo_ip;
extern const field_meta hfm_nas_5gs_mm_conf_upd_ind_red_b1;
extern const field_meta hfm_mm_s1_mode_b0;
extern const field_meta hfm_mm_ho_attach_b1;
extern const field_meta hfm_mm_lpp_cap_b2;
extern const field_meta hfm_mm_type_id;
extern const field_meta hfm_mm_odd_even;
extern const field_meta hfm_mm_length;
extern const field_meta hfm_mm_abba;
extern const field_meta hfm_mm_pld_cont;
extern const field_meta hfm_mm_req_type;
extern const field_meta hfm_mm_serv_type;
extern const field_meta hfm_mm_5g_ea0;
extern const field_meta hfm_mm_128_5g_ea1;
extern const field_meta hfm_mm_128_5g_ea2;
extern const field_meta hfm_mm_128_5g_ea3;
extern const field_meta hfm_mm_5g_ea4;
extern const field_meta hfm_mm_5g_ea5;
extern const field_meta hfm_mm_5g_ea6;
extern const field_meta hfm_mm_5g_ea7;
extern const field_meta hfm_mm_5g_ia0;
extern const field_meta hfm_mm_5g_128_ia1;
extern const field_meta hfm_mm_5g_128_ia2;
extern const field_meta hfm_mm_5g_128_ia3;
extern const field_meta hfm_mm_5g_ia4;
extern const field_meta hfm_nas_5gs_mm_5g_ia5;
extern const field_meta hfm_nas_5gs_mm_5g_ia6;
extern const field_meta hfm_nas_5gs_mm_5g_ia7;
extern const field_meta hfm_nas_5gs_mm_eea0;
extern const field_meta hfm_nas_5gs_mm_128eea1;
extern const field_meta hfm_nas_5gs_mm_128eea2;
extern const field_meta hfm_nas_5gs_mm_eea3;
extern const field_meta hfm_nas_5gs_mm_eea4;
extern const field_meta hfm_nas_5gs_mm_eea5;
extern const field_meta hfm_nas_5gs_mm_eea6;
extern const field_meta hfm_nas_5gs_mm_eea7;
extern const field_meta hfm_nas_5gs_mm_eia0;
extern const field_meta hfm_nas_5gs_mm_128eia1;
extern const field_meta hfm_nas_5gs_mm_128eia2;
extern const field_meta hfm_nas_5gs_mm_eia3;
extern const field_meta hfm_nas_5gs_mm_eia4;
extern const field_meta hfm_nas_5gs_mm_eia5;
extern const field_meta hfm_nas_5gs_mm_eia6;
extern const field_meta hfm_nas_5gs_mm_eia7;
extern const field_meta hf_mm_n1_mode_reg_b1;
extern const field_meta hf_mm_s1_mode_reg_b0;
extern const field_meta hf_mm_sal_t_li;
// extern const field_meta hf_proc_trans_id;
extern const field_meta hf_element;
extern const field_meta hf_mm_sal_al_t;
extern const field_meta hf_abba;
extern const field_meta hf_sal_num_e;

extern const true_false_string tfs_follow_on_req;
extern const true_false_string tfs_mm_tsc;
extern const true_false_string tfs_sms_requested;

/* 9.11.3.7    5GS registration type */
extern const val_string        values_registration_type[];

extern const field_meta        hf_5gs_reg_type;
extern const field_meta        hf_tsc;
extern const field_meta        hf_sms_requested;
extern const field_meta        hf_sd;

extern const field_meta hf_nas_key_set_id_h1;
extern const field_meta hf_tsc_h1;
extern const field_meta hf_nas_key_set_id;
extern const field_meta hfm_mm_raai_b0;
extern const field_meta hf_mapped_conf_sst;
extern const field_meta hf_mapped_conf_ssd;
extern const field_meta hf_mm_sprti;
} // namespace mm
