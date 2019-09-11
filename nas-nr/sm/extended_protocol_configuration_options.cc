#include "../dissect_sm_msg.hh"
#include "../range_string.hh"

const field_meta hf_gsma_sm_ext = {
    "Extension",
    "nas_5gs.gsm.sm.ext",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x80,
};
const field_meta hf_gsma_conf_prot = {
    "Configuration Protocol",
    "nas_5gs.gsm.sm.configuration_protocol",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x7,
};
extern const value_string gsm_a_gm_link_dir_vals[] = {
    {0 - 1u, "Unknown"},
    {0x0, "MS to network"},
    {0x1, "Network to MS"},
    {0, nullptr},
};

extern const value_string gsm_a_gm_sel_bearer_ctrl_mode_vals[] = {
    {1, "MS only"},
    {2, "MS/NW"},
    {0, nullptr},
};

extern const value_string gsm_a_gm_nbifom_mode_vals[] = {
    {0, "UE-initiated"},
    {1, "Network-initiated"},
    {0, nullptr},
};

const true_false_string gsm_a_gm_apn_rate_ctrl_params_aer_value = {
    "Additional exception reports at maximum rate reached are allowed",
    "Additional exception reports at maximum rate reached are not allowed"};

extern const value_string gsm_a_gm_apn_rate_ctrl_ul_time_unit_vals[] = {
    {0, "Unrestricted"},
    {1, "Minute"},
    {2, "Hour"},
    {3, "Day"},
    {4, "Week"},
    {0, nullptr},
};

extern const value_string gsm_a_gm_sm_pco_3gpp_data_off_ue_status_vals[] = {
    {1, "Deactivated"},
    {2, "Activated"},
    {0, nullptr},
};

extern const value_string ppp_vals[];

const field_meta hf_proto_id = {
    "Protocol ID",
    "nas_5gs.protocol.id",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// Extended protocol configuration options  9.11.4.6
int sm::dissect_ext_pco(dissector d, context* ctx) {
    const use_context uc(ctx, "extended-protocol-conf-options", d, -1);

    // See subclause 10.5.6.3A in 3GPP TS 24.008    

    /* 1 ext 0 0 0 0 Spare  Configuration protocol */
    (void) d.add_item(1, &hf_gsma_sm_ext, enc::be);
    (void) d.add_item(1, &hf_gsma_conf_prot, enc::be);
    d.step(1);

    return uc.length;
}

// Extended protocol configuration options  9.11.4.6
const element_meta sm::ext_pco = {
    0x7B,
    "Extended protocol configuration options",
    sm::dissect_ext_pco,
    nullptr,
};

// only part
extern const value_string ppp_vals[] = {
    {1, "Padding Protocol"},
    {3, "ROHC small-CID"},
    {5, "ROHC large-CID"},
    {0x21, "Internet Protocol version 4"},
    {0x23, "OSI Network Layer"},
    {0x25, "Xerox NS IDP"},
    {0x27, "DECnet Phase IV"},
    {0x29, "Appletalk"},
    {0x57, "Internet Protocol version 6"},
    {0x4b, "SNA over 802.2"},
    {0x4d, "SNA"},
    {0, nullptr},
};


extern const range_string gsm_a_sm_pco_ms2net_prot_vals[] = {
    {0x0001, 0x0001, "P-CSCF IPv6 Address Request"},
    {0x0002, 0x0002, "IM CN Subsystem Signaling Flag"},
    {0x0003, 0x0003, "DNS Server IPv6 Address Request"},
    {0x0004, 0x0004, "Not Supported"},
    {0x0005, 0x0005, "MS Support of Network Requested Bearer Control indicator"},
    {0x0006, 0x0006, "Reserved"},
    {0x0007, 0x0007, "DSMIPv6 Home Agent Address Request"},
    {0x0008, 0x0008, "DSMIPv6 Home Network Prefix Request"},
    {0x0009, 0x0009, "DSMIPv6 IPv4 Home Agent Address Request"},
    {0x000a, 0x000a, "IP address allocation via NAS signalling"},
    {0x000b, 0x000b, "IPv4 address allocation via DHCPv4"},
    {0x000c, 0x000c, "P-CSCF IPv4 Address Request"},
    {0x000d, 0x000d, "DNS Server IPv4 Address Request"},
    {0x000e, 0x000e, "MSISDN Request"},
    {0x000f, 0x000f, "IFOM-Support-Request"},
    {0x0010, 0x0010, "IPv4 Link MTU Request"},
    {0x0011, 0x0011, "MS support of Local address in TFT indicator"},
    {0x0012, 0x0012, "P-CSCF Re-selection support"},
    {0x0013, 0x0013, "NBIFOM request indicator"},
    {0x0014, 0x0014, "NBIFOM mode"},
    {0x0015, 0x0015, "Non-IP Link MTU Request"},
    {0x0016, 0x0016, "APN rate control support indicator"},
    {0x0017, 0x0017, "3GPP PS data off UE status"},
    {0x0018, 0x0018, "Reliable Data Service request indicator"},
    {0x0019, 0x0019, "Additional APN rate control for exception data support indicator"},
    {0x001a, 0x001a, "PDU session ID"},
    {0x001b, 0x001f, "Reserved"},
    {0x0020, 0x0020, "Ethernet Frame Payload MTU Request"},
    {0x0021, 0x0021, "Unstructured Link MTU Request"},
    {0x0022, 0x0022, "5GSM cause value"},
    {0x0023, 0x0023, "QoS rules with the length of two octets support indicator"},
    {0x0024,
     0x0024,
     "QoS flow descriptions with the length of two octets support indicator"},
    {0xff00, 0xffff, "Operator Specific Use"},
    {0, 0, nullptr},
};
extern const range_string gsm_a_sm_pco_net2ms_prot_vals[] = {
    {0x0001, 0x0001, "P-CSCF IPv6 Address"},
    {0x0002, 0x0002, "IM CN Subsystem Signaling Flag"},
    {0x0003, 0x0003, "DNS Server IPv6 Address"},
    {0x0004, 0x0004, "Policy Control rejection code"},
    {0x0005, 0x0005, "Selected Bearer Control Mode"},
    {0x0006, 0x0006, "Reserved"},
    {0x0007, 0x0007, "DSMIPv6 Home Agent Address"},
    {0x0008, 0x0008, "DSMIPv6 Home Network Prefix"},
    {0x0009, 0x0009, "DSMIPv6 IPv4 Home Agent Address"},
    {0x000a, 0x000a, "Reserved"},
    {0x000b, 0x000b, "Reserved"},
    {0x000c, 0x000c, "P-CSCF IPv4 Address"},
    {0x000d, 0x000d, "DNS Server IPv4 Address"},
    {0x000e, 0x000e, "MSISDN"},
    {0x000f, 0x000f, "IFOM-Support"},
    {0x0010, 0x0010, "IPv4 Link MTU"},
    {0x0011, 0x0011, "Network support of Local address in TFT indicator"},
    {0x0012, 0x0012, "Reserved"},
    {0x0013, 0x0013, "NBIFOM accepted indicator"},
    {0x0014, 0x0014, "NBIFOM mode"},
    {0x0015, 0x0015, "Non-IP Link MTU"},
    {0x0016, 0x0016, "APN rate control parameters"},
    {0x0017, 0x0017, "3GPP PS data off support indication"},
    {0x0018, 0x0018, "Reliable Data Service accepted indicator"},
    {0x0019, 0x0019, "Additional APN rate control for exception data parameters"},
    {0x001a, 0x001a, "Reserved"},
    {0x001b, 0x001b, "S-NSSAI"},
    {0x001c, 0x001c, "QoS rules"},
    {0x001d, 0x001d, "Session-AMBR"},
    {0x001e, 0x001e, "PDU session address lifetime"},
    {0x001f, 0x001f, "QoS flow descriptions"},
    {0x0020, 0x0020, "Ethernet Frame Payload MTU"},
    {0x0021, 0x0021, "Unstructured Link MTU"},
    {0x0022, 0x0022, "Reserved"},
    {0x0023, 0x0023, "QoS rules with the length of two octets"},
    {0x0024, 0x0024, "QoS flow descriptions with the length of two octets"},
    {0xff00, 0xffff, "Operator Specific Use"},
    {0, 0, nullptr},
};
