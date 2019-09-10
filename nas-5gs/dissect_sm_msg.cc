#include "dissect_sm_msg.hh"
#include "dissect_nas5g.hh"
#include "ber.hh"
#include "common.hh"

/* 8.3 5GS session management messages */

using namespace cmn;
using namespace sm;

extern const message_meta sm::msgs[] = {
    {
        0xc1,
        "PDU session establishment request",
        dissect_pdu_ses_establishment_req,
        nullptr,
    },
    {
        0xc2,
        "PDU session establishment accept",
        dissect_pdu_ses_establishment_accept,
        nullptr,
    },
    {
        0xc3,
        "PDU session establishment reject",
        dissect_pdu_ses_establishment_rej,
        nullptr,
    },

    {
        0xc4,
        "Not used in current version",
        no_dissect,
        nullptr,
    },
    {
        0xc5,
        "PDU session authentication command",
        dissect_pdu_ses_authentication_cmd,
        nullptr,
    },

    {
        0xc6,
        "PDU session authentication complete",
        dissect_pdu_ses_authentication_cmpl,
        nullptr,
    },
    {
        0xc7,
        "PDU session authentication result",
        no_dissect,
        nullptr,
    },
    {
        0xc8,
        "Not used in current version",
        no_dissect,
        nullptr,
    },

    {
        0xc9,
        "PDU session modification request",
        dissect_pdu_ses_modification_req,
        nullptr,
    },
    {
        0xca,
        "PDU session modification reject",
        dissect_pdu_ses_modification_rej,
        nullptr,
    },
    {
        0xcb,
        "PDU session modification command",
        dissect_pdu_ses_modification_cmd,
        nullptr,
    },
    {
        0xcc,
        "PDU session modification complete",
        dissect_pdu_ses_modification_cmpl,
        nullptr,
    },
    {
        0xcd,
        "PDU session modification command reject",
        dissect_pdu_session_modification_command_reject,
        nullptr,
    },

    {
        0xce,
        "Not used in current version",
        no_dissect,
        nullptr,
    },
    {
        0xcf,
        "Not used in current version",
        no_dissect,
        nullptr,
    },
    {
        0xd0,
        "Not used in current version",
        no_dissect,
        nullptr,
    },

    {
        0xd1,
        "PDU session release request",
        dissect_pdu_ses_release_req,
        nullptr,
    },
    {
        0xd2,
        "PDU session release reject",
        dissect_pdu_ses_release_rej,
        nullptr,
    },
    {
        0xd3,
        "PDU session release command",
        dissect_pdu_ses_release_cmd,
        nullptr,
    },
    {
        0xd4,
        "PDU session release complete",
        dissect_pdu_ses_release_cmpl,
        nullptr,
    },

    {
        0xd5,
        "Not used in current version",
        no_dissect,
        nullptr,
    },

    {
        0xd6,
        "5GSM status",
        dissect_sm_status,
        nullptr,
    },
    {0, nullptr, nullptr, nullptr},
};


// Back-off timer value    GPRS timer 3 9.11.2.25
const element_meta sm::backoff_gprs_timer3 = {
    0x37,
    "GPRS timer 3 - Back-off timer value",
    dissect_gprs_timer3_set,
    nullptr,
};

// RQ timer value    GPRS timer 9.11.2.3
const element_meta sm::rq_gprs_timer = {
    0x56,
    "GPRS timer- RQ timer time",
    dissect_gprs_timer_set,
    nullptr,
};

extern const value_string sm::sm_pf_type_values[] = {
    {0x01, "Match-all type"},
    {0x10, "IPv4 remote address type"},
    {0x11, "IPv4 local address type"},
    {0x21, "IPv6 remote address/prefix length type"},
    {0x23, "IPv6 local address/prefix length type"},
    {0x30, "Protocol identifier/Next header type"},
    {0x40, "Single local port type"},
    {0x41, "Local port range type"},
    {0x50, "Single remote port type"},
    {0x51, "Remote port range type"},
    {0x60, "Security parameter index type"},
    {0x70, "Type of service/Traffic class type"},
    {0x80, "Flow label type"},
    {0x81, "Destination MAC address type"},
    {0x82, "Source MAC address type"},
    {0x83, "802.1Q C-TAG VID type"},
    {0x84, "802.1Q S-TAG VID type"},
    {0x85, "802.1Q C-TAG PCP/DEI type"},
    {0x86, "802.1Q S-TAG PCP/DEI type"},
    {0x87, "Ethertype type"},
    {0, nullptr},
};

extern const value_string sm::sm_pkt_flt_dir_values[] = {
    {0x00, "Reserved"},
    {0x01, "Downlink only"},
    {0x02, "Uplink only"},
    {0x03, "Bidirectional"},
    {0, nullptr},
};
#if 0
const field_meta sm::hf_sm_length = {
    "Length",
    "nas_5gs.sm.length",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#endif

const field_meta sm::hf_sm_pkt_flt_id = {
    "Packet filter identifier",
    "nas_5gs.sm.pkt_flt_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};
const field_meta sm::hf_sm_pkt_flt_dir = {
    "Packet filter direction",
    "nas_5gs.sm.pkt_flt_dir",
    ft::ft_uint8,
    fd::base_dec,
    (sm_pkt_flt_dir_values),
    nullptr,
    nullptr,
    0x30,
};
#if 0
const field_meta sm::hf_sm_pf_len = {
    "Length",
    "nas_5gs.sm.pf_len",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
#endif

const field_meta sm::hf_sm_pf_type = {
    "Packet filter component type",
    "nas_5gs.sm.pf_type",
    ft::ft_uint8,
    fd::base_dec,
    (sm_pf_type_values),
    nullptr,
    nullptr,
    0x0,
};

