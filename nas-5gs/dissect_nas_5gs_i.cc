#include "dissect_nas_5gs.hh"

static field_meta hfm_nas_5gs_msg_elems = {
    "Message Elements",
    "nas_5gs.message_elements",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_nas_5gs_msg_elems = &hfm_nas_5gs_msg_elems;

__declspec(selectany) extern const val_string nas_5gs_epd_vals[] = {
    {0x00, "Group call control"},
    {0x01, "Broadcast call control"},
    {0x02, "EPS session management messages"},
    {0x03, "Call Control; call related SS messages"},
    {0x04, "GPRS Transparent Transport Protocol (GTTP)"},
    {0x05, "Mobility Management messages"},
    {0x06, "Radio Resources Management messages"},
    {0x07, "EPS mobility management messages"},
    {0x08, "GPRS mobility management messages"},
    {0x09, "SMS messages"},
    {0x0a, "GPRS session management messages"},
    {0x0b, "Non call related SS messages"},
    {0x0c, "Location services specified in 3GPP TS 44.071"},
    {0x0d, "Unknown"},
    {0x0e, "Reserved for extension of the PD to one octet length "},
    {0x0f,
     "Tests procedures described in 3GPP TS 44.014, 3GPP TS 34.109 and 3GPP TS 36.509"},
    {0x2e, "5G session management messages"},
    {0x7e, "5G mobility management messages"},
    {0, nullptr},
};
static const field_meta hfm_nas_5gs_epd = {
    "Extended protocol discriminator",
    "nas_5gs.epd",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_epd_vals,
    nullptr,
    nullptr,
    0x0,
};
__declspec(selectany) extern const field_meta* hf_nas_5gs_epd = &hfm_nas_5gs_epd;

static field_meta hfm_nas_5gs_spare_half_octet = {
    "Spare Half Octet",
    "nas_5gs.spare_half_octet",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
extern const field_meta* hf_nas_5gs_spare_half_octet = &hfm_nas_5gs_spare_half_octet;

__declspec(selectany) extern const val_string nas_5gs_security_header_type_vals[] = {
    {0, "Plain NAS message, not security protected"},
    {1, "Integrity protected"},
    {2, "Integrity protected and ciphered"},
    {3, "Integrity protected with new 5GS security context"},
    {4, "Integrity protected and ciphered with new 5GS security context"},
    {0, nullptr},
};

static field_meta hfm_nas_5gs_security_header_type = {
    "Security header type",
    "nas_5gs.security_header_type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_security_header_type_vals,
    nullptr,
    nullptr,
    0x0f,
};
extern const field_meta* hf_nas_5gs_security_header_type =
    &hfm_nas_5gs_security_header_type;

static field_meta hfm_nas_5gs_msg_auth_code = {
    "Message authentication code",
    "nas_5gs.msg_auth_code",
    ft::ft_uint32,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_nas_5gs_msg_auth_code = &hfm_nas_5gs_msg_auth_code;

static field_meta hfm_nas_5gs_seq_no = {
    "Sequence number",
    "nas_5gs.seq_no",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_nas_5gs_seq_no = &hfm_nas_5gs_seq_no;

/* 5GS session management messages */
extern const val_string nas_5gs_sm_message_type_vals[] = {

    {0xc1, "PDU session establishment request"},
    {0xc2, "PDU session establishment accept"},
    {0xc3, "PDU session establishment reject"},

    {0xc4, "Not used in current version"},
    {0xc5, "PDU session authentication command"},

    {0xc6, "PDU session authentication complete"},
    {0xc7, "PDU session authentication result"},
    {0xc8, "Not used in current version"},

    {0xc9, "PDU session modification request"},
    {0xca, "PDU session modification reject"},
    {0xcb, "PDU session modification command"},
    {0xcc, "PDU session modification complete"},
    {0xcd, "PDU session modification command reject"},

    {0xce, "Not used in current version"},
    {0xcf, "Not used in current version"},
    {0xd0, "Not used in current version"},

    {0xd1, "PDU session release request"},
    {0xd2, "PDU session release reject"},
    {0xd3, "PDU session release command"},
    {0xd4, "PDU session release complete"},

    {0xd5, "Not used in current version"},

    {0xd6, "5GSM status"},
    {0, nullptr},
};

static field_meta hfm_nas_5gs_sm_msg_type = {
    "Message type",
    "nas_5gs.sm.message_type",
    ft::ft_uint8,
    fd::base_hex | fd::base_ext_string,
    nas_5gs_sm_message_type_vals,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_nas_5gs_sm_msg_type     = &hfm_nas_5gs_sm_msg_type;


extern const val_string nas_5gs_pdu_session_id_vals[] = {
    {0x00, "No PDU session identity assigned"},
    {0x01, "Reserved"},
    {0x02, "Reserved"},
    {0x03, "Reserved"},
    {0x04, "Reserved"},
    {0x05, "PDU session identity value 5"},
    {0x06, "PDU session identity value 6"},
    {0x07, "PDU session identity value 7"},
    {0x08, "PDU session identity value 8"},
    {0x09, "PDU session identity value 9"},
    {0x0a, "PDU session identity value 10"},
    {0x0b, "PDU session identity value 11"},
    {0x0c, "PDU session identity value 12"},
    {0x0d, "PDU session identity value 13"},
    {0x0e, "PDU session identity value 14"},
    {0x0f, "PDU session identity value 15"},
    {0, nullptr},
};
static field_meta hfm_nas_5gs_pdu_session_id = {
    "PDU session identity",
    "nas_5gs.pdu_session_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_pdu_session_id_vals,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_nas_5gs_pdu_session_id = &hfm_nas_5gs_pdu_session_id;


static field_meta hfm_nas_5gs_proc_trans_id = {
    "Procedure transaction identity",
    "nas_5gs.proc_trans_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta* hf_nas_5gs_proc_trans_id = &hfm_nas_5gs_proc_trans_id;
