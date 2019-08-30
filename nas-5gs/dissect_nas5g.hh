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
int dissect_eap_msg(dissector d, context* ctx);

extern const true_false_string tfs_allowed_not_allowed;
// extern const true_false_string tfs_follow_on_req;

extern const element_meta eap_msg;
extern const field_meta*  hf_msg_elem;
extern const field_meta*  hf_spare_half_octet;
extern const field_meta*  hf_epd;
extern const field_meta*  hf_pdu_sess_id;
extern const field_meta*  hf_mm_msg_type;
extern const field_meta*  hf_sm_msg_type;
extern const field_meta*  hf_sec_header_type;
extern const field_meta*  hf_msg_auth_code;
extern const field_meta   hf_pdu_ipv4_mask;
extern const field_meta   hf_pid_next_hd;
extern const field_meta   hf_single_port_type;
// extern const field_meta   hf_5gs_reg_type;
// extern const field_meta   hf_tsc_h1;
// extern const field_meta   hf_nas_key_set_id_h1;

extern const field_meta   hf_dnn;
extern const field_meta   hf_spare_b7;
extern const field_meta   hf_spare_b6;
extern const field_meta   hf_spare_b5;
extern const field_meta   hf_spare_b4;
extern const field_meta   hf_spare_b3;
extern const field_meta   hf_spare_b2;
extern const field_meta   hf_spare_b1;
extern const field_meta*  hf_seq_no;
extern const field_meta*  hf_proc_trans_id;

} // namespace nas
