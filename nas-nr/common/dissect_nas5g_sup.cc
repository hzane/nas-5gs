#include "common.hh"
#include "dissect_nas5g.hh"

using namespace cmn;
using namespace nas;

const field_meta hfm_msg_elements = {
    "Message Elements",
    "nas.nr.message_elements",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_msg_elem = &hfm_msg_elements;

extern const v_string epd_values[] = {
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
     "Tests procedures described in 3GPP TS 44.014, 3GPP TS 34.109 and 3GPP TS 36.509",},
    {0x2e, "5G session management messages"},
    {0x7e, "5G mobility management messages"},
    {0, nullptr},
};

const field_meta hfm_epd = {
    "Extended protocol discriminator",
    "nas.nr.epd",
    ft::ft_uint8,
    fd::base_dec,
    epd_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_epd = &hfm_epd;

const v_string security_header_type_values[] = {
    {0, "Plain NAS message, not security protected"},
    {1, "Integrity protected"},
    {2, "Integrity protected and ciphered"},
    {3, "Integrity protected with new 5GS security context"},
    {4, "Integrity protected and ciphered with new 5GS security context"},
    {0, nullptr},
};

field_meta hfm_security_header_type = {
    "Security header type",
    "nas.nr.security_header_type",
    ft::ft_uint8,
    fd::base_dec,
    security_header_type_values,
    nullptr,
    nullptr,
    0x0f,
};
const field_meta* nas::hf_security_header_type = &hfm_security_header_type;

field_meta hfm_msg_auth_code = {
    "Message authentication code",
    "nas.nr.msg_auth_code",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_msg_auth_code = &hfm_msg_auth_code;

/* 5GS session management messages */
const v_string sm_message_type_values[] = {

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

field_meta hfm_sm_message_type = {
    "Message type",
    "nas.nr.sm.message.type",
    ft::ft_uint8,
    fd::base_hex,
    sm_message_type_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_sm_msg_type = &hfm_sm_message_type;


field_meta hfm_proc_trans_id = {
    "Procedure transaction identity",
    "nas.nr.procedure.transaction.id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_procedure_transaction_id = &hfm_proc_trans_id;

/* 9.7  Message type */

/* 5GS mobility management messages */
const v_string mm_message_type_values[] = {
    {0x41, "Registration request"},
    {0x42, "Registration accept"},
    {0x43, "Registration complete"},
    {0x44, "Registration reject"},
    {0x45, "Deregistration request (UE originating)"},
    {0x46, "Deregistration accept (UE originating)"},
    {0x47, "Deregistration request (UE terminated)"},
    {0x48, "Deregistration accept (UE terminated)"},

    {0x49, "Not used in current version"},
    {0x4a, "Not used in current version"},
    {0x4b, "Not used in current version"},

    {0x4c, "Service request"},
    {0x4d, "Service reject"},
    {0x4e, "Service accept"},

    {0x4f, "Not used in current version"},
    {0x50, "Not used in current version"},
    {0x51, "Not used in current version"},
    {0x52, "Not used in current version"},
    {0x53, "Not used in current version"},

    {0x54, "Configuration update command"},
    {0x55, "Configuration update complete"},
    {0x56, "Authentication request"},
    {0x57, "Authentication response"},
    {0x58, "Authentication reject"},
    {0x59, "Authentication failure"},

    {0x5a, "Authentication result"},
    {0x5b, "Identity request"},
    {0x5c, "Identity response"},
    {0x5d, "Security mode command"},
    {0x5e, "Security mode complete"},
    {0x5f, "Security mode reject"},

    {0x60, "Not used in current version"},
    {0x61, "Not used in current version"},
    {0x62, "Not used in current version"},
    {0x63, "Not used in current version"},
    {0x64, "5GMM status"},
    {0x65, "Notification"},
    {0x66, "Notification response"},
    {0x67, "UL NAS transport"},
    {0x68, "DL NAS transport"},
    {0, nullptr},
};
const field_meta hfm_mm_msg_type = {
    "Message type",
    "nas.nr.mm.message.type",
    ft::ft_uint8,
    fd::base_hex,
    mm_message_type_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* nas::hf_mm_msg_type = &hfm_mm_msg_type;

const field_meta nas::hf_service_request_msg_id = {
    "Service request message identity",
    "nas.nr.mm.message.identity.type",
    ft::ft_uint8,
    fd::base_hex,
    mm_message_type_values,
    nullptr,
    nullptr,
    0x0,
};

// GPRS timer 3 9.11.2.4
const element_meta nas::t3348_gprs_timer3{
    0xff,
    "GPRS timer3 - T4448 value",
    dissect_gprs_timer3_set,
    nullptr,
};


const field_meta nas::hf_pdu_ipv4_mask = {
    "IPv4 address mask",
    "nas.nr.ipv4.address.mask",
    ft::ft_uint32,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta nas::hf_pid_next_hd = {
    "Protocol identifier/Next header type",
    "nas.nr.protocol.identifier.next.hd",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta nas::hf_single_port_type = {
    "Port type",
    "nas.nr.port.type",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
