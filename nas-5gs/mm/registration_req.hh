#pragma once


namespace mm_reg_req {
extern const field_meta* hf_reg_req_flags;

extern const element_meta nw_slicing_ind;
extern const element_meta eps_nas_msg_cont;
extern const element_meta ue_status;
extern const element_meta last_v_tai;
extern const element_meta nksi_key_set_id;
extern const element_meta pld_cont;
extern const element_meta ladn_ind;
extern const element_meta ue_sec_cap;
extern const element_meta mm_cap;
extern const element_meta ul_data_status;
extern const element_meta s1_ue_net_cap;
extern const element_meta ue_usage_set;
extern const element_meta allow_pdu_ses_sts;
extern const element_meta aguti_mobile_id;
extern const element_meta pld_cont_type;
extern const element_meta update_type;
extern const element_meta requested_drx_param;
extern const element_meta mico_ind;
extern const element_meta requested_nssai;

extern const field_meta hf_ngksi_nas_ksi;
extern const field_meta hf_mm_for;
extern const field_meta hf_mm_reg_type;

extern const element_meta registration_request_type;

int dissect_reg_req_type(dissector d, context* ctx);

} // namespace mm_reg_req
