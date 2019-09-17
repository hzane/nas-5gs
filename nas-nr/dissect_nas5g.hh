#pragma once
#include "core.hh"
#include "field_meta.hh"

// dissect_msg_fnc_t
int dissect_sm_msg(dissector d, context* ctx);
int dissect_mm_msg(dissector d, context* ctx);

int dissect_nas5g_plain(dissector d, context* ctx);
int dissect_nas5g_security_protected(dissector d, context* ctx);

const message_meta* find_dissector(uint8_t iei, const message_meta* meta);

namespace nas {

extern const element_meta t3348_gprs_timer3;
extern const field_meta*  hf_msg_elem;
extern const field_meta*  hf_epd;
extern const field_meta*  hf_pdu_sess_id;
extern const field_meta*  hf_mm_msg_type;
extern const field_meta*  hf_sm_msg_type;
extern const field_meta*  hf_sec_header_type;
extern const field_meta*  hf_msg_auth_code;
extern const field_meta   hf_pdu_ipv4_mask;
extern const field_meta   hf_pid_next_hd;
extern const field_meta   hf_single_port_type;
extern const field_meta*  hf_sequence_no;
extern const field_meta*  hf_proc_trans_id;
extern const field_meta   hf_service_request_msg_id; // TODO: check the ie

inline extern const true_false_string tfs_supported_not_supported = {
    "Supported",
    "Not supported",
};

inline extern const true_false_string tfs_allowed_not_allowed = {
    "Allowed",
    "Not Allowed",
};
} // namespace nas
