#include "../common/dissect_sm_msg.hh"

// 5GSM cause 9.11.4.2
int sm::dissect_nrsm_cause(dissector d, context* ctx) {
    const use_context uc(ctx, "5gsm-cause", d, -1);

    (void) d.add_item(1, &hf_nrsm_cause, enc::be);
    d.step(1);

    return 1;
}

struct nrsm_cause_t {
    uint8_t cause;
};

// 5GSM cause 9.11.4.2
const element_meta sm::nrsm_cause = {
    0x59,
    nullptr,
    sm::dissect_nrsm_cause,
    nullptr,
};

/* * 9.11.4.2    5GSM cause */
extern const v_string sm::nrsm_cause_values[] = {
    {0x1a, "Insufficient resources"},
    {0x1b, "Missing or unknown DNN"},
    {0x1c, "Unknown PDU session type"},
    {0x1d, "User authentication or authorization failed"},
    {0x1f, "Request rejected, unspecified"},
    {0x22, "Service option temporarily out of order"},
    {0x23, "PTI already in use"},
    {0x24, "Regular deactivation"},
    {0x27, "Reactivation requested"},
    {0x2b, "Invalid PDU session identity"},
    {0x2c, "Semantic errors in packet filter(s)"},
    {0x2d, "Syntactical error in packet filter(s)"},
    {0x2e, "Out of LADN service area"},
    {0x2f, "PTI mismatch"},
    {0x32, "PDU session type Ipv4 only allowed"},
    {0x33, "PDU session type Ipv6 only allowed"},
    {0x36, "PDU session does not exist"},
    {0x43, "Insufficient resources for specific slice and DNN"},
    {0x44, "Not supported SSC mode"},
    {0x45, "Insufficient resources for specific slice"},
    {0x46, "Missing or unknown DNN in a slice"},
    {0x51, "Invalid PTI value"},
    {0x52, "Maximum data rate per UE for user-plane integrity protection is too low"},
    {0x53, "Semantic error in the QoS operation"},
    {0x54, "Syntactical error in the QoS operation"},
    {0x55, "Invalid mapped EPS bearer identity"},
    {0x5f, "Semantically incorrect message"},
    {0x60, "Invalid mandatory information"},
    {0x61, "Message type non - existent or not implemented"},
    {0x62, "Message type not compatible with the protocol state"},
    {0x63, "Information element non - existent or not implemented"},
    {0x64, "Conditional IE error"},
    {0x65, "Message not compatible with the protocol state"},
    {0x6f, "Protocol error, unspecified"},
    {0, nullptr},
};
const field_meta sm::hf_nrsm_cause = {
    "5GSM cause",
    "nas.nr.sm.cause",
    ft::ft_uint8,
    fd::base_dec,
    sm::nrsm_cause_values,
    nullptr,
    nullptr,
    0x0,
};
