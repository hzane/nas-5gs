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
extern const field_meta*  hf_spare_half_octet_invisible;
extern const field_meta*  hf_epd;
extern const field_meta*  hf_pdu_sess_id;
extern const field_meta*  hf_mm_msg_type;
extern const field_meta*  hf_sm_msg_type;
extern const field_meta*  hf_sec_header_type;
extern const field_meta*  hf_msg_auth_code;
extern const field_meta   hf_pdu_ipv4_mask;
extern const field_meta   hf_pid_next_hd;
extern const field_meta   hf_single_port_type;
extern const field_meta*  hf_seq_no;
extern const field_meta*  hf_proc_trans_id;
extern const field_meta   hf_service_request_msg_id;

inline extern const field_meta hf_spare_b7 = {
    "Spare",
    "nas_5gs.spare_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x80,
};
inline __declspec(selectany) extern const field_meta hf_spare_b6 = {
    "Spare",
    "nas_5gs.spare_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x40,
};
inline __declspec(selectany) extern const field_meta hf_spare_b5 = {
    "Spare",
    "nas_5gs.spare_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x20,
};
inline __declspec(selectany) extern const field_meta hf_spare_b4 = {
    "Spare",
    "nas_5gs.spare_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x10,
};
inline __declspec(selectany) extern const field_meta hf_spare_b3 = {
    "Spare",
    "nas_5gs.spare_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x08,
};
inline __declspec(selectany) extern const field_meta hf_spare_b2 = {
    "Spare",
    "nas_5gs.spare_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x04,
};

inline __declspec(selectany) extern const field_meta hf_spare_b1 = {
    "Spare",
    "nas_5gs.spare_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x02,
};

inline __declspec(selectany) extern const field_meta hf_spare_b0 = {
    "Spare",
    "nas_5gs.spare.b0",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
};

inline __declspec(selectany) extern const true_false_string tfs_supported_not_supported = {
    "Supported",
    "Not supported",
};

inline extern const true_false_string tfs_allowed_not_allowed = {
    "Allowed",
    "Not Allowed",
};
} // namespace nas
