#pragma once
#include "core.hh"
#include "field_meta.hh"

// dissect_msg_fnc_t
int dissect_sm_msg(dissector d, context* ctx = nullptr);
int dissect_mm_msg(dissector d, context* ctx = nullptr);

int dissect_nas5g_plain(dissector d, context* ctx = nullptr);

const message_meta* find_dissector(uint8_t iei, const message_meta* meta);

namespace nas {

int dissect_dnn(dissector d, context* ctx);
int dissect_s_nssai(dissector d, context* ctx);
int dissect_eap_msg(dissector d, context* ctx);

extern const field_meta* hf_msg_elem;
extern const field_meta* hf_spare_half_octet;
extern const field_meta* hf_epd;
extern const field_meta* hf_pdu_session_id;
extern const field_meta* hf_mm_msg_type;
extern const field_meta* hf_sm_msg_type;
extern const field_meta* hf_sec_header_type;

extern const element_meta eap_msg;
extern const field_meta   hf_sal_num_e;

extern const field_meta* hf_msg_auth_code;
extern const field_meta* hf_mm_follow_on_req;
extern const field_meta  hf_sms_requested;
extern const field_meta  hf_5gs_reg_type;
extern const field_meta  hf_tsc;
extern const field_meta  hf_tsc_h1;
extern const field_meta  hf_nas_key_set_id_h1;
extern const field_meta  hf_5gmm_cause;
extern const field_meta  hf_nas_5gs_mm_sst;
extern const field_meta  hf_nas_key_set_id;
extern const field_meta  hf_follow_on_req;
extern const field_meta  hf_mm_sal_t_li;
extern const field_meta  hf_nas_5gs_mm_sal_al_t;
extern const field_meta  hf_nas_5gs_mm_s1_mode_reg_b0;
extern const field_meta  hf_nas_5gs_mm_n1_mode_reg_b1;
extern const field_meta  hf_sst;
extern const field_meta  hf_sd;
extern const field_meta  hf_mapped_conf_sst;
extern const field_meta  hf_mapped_conf_ssd;
extern const field_meta  hf_dnn;

extern const true_false_string tfs_allowed_not_allowed;

extern const field_meta  hf_spare_b7;
extern const field_meta  hf_spare_b6;
extern const field_meta  hf_spare_b5;
extern const field_meta  hf_spare_b4;
extern const field_meta  hf_spare_b3;
extern const field_meta  hf_spare_b2;
extern const field_meta  hf_spare_b1;
extern const field_meta* hf_seq_no;
extern const field_meta* hf_proc_trans_id;
extern const field_meta  nas::hf_sst;
} // namespace nas
