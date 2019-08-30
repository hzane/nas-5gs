#include "dissect_nas_5gs.hh"
#include "dissect_sm_msg.hh"
#include "ts24007.hh"

using namespace nas;

/* 8.3 5GS session management messages */

/*
 * 8.3.6 PDU session authentication result
 */
int sm::pdu_ses_auth_res(dissector d, context* ctx) {
    auto start = d.offset;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*EAP message    EAP message 9.11.2.2    M    LV-E    6-1502 */
    // ELEM_MAND_LV_E(NAS_5GS_PDU_TYPE_COMMON,
    //                DE_NAS_5GS_CMN_EAP_MESSAGE,
    //                NULL,
    //                ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_lv_e(nullptr, &eap_msg, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options    9.11.4.2    O    TLV - E    4 - 65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.offset - start;
}

/*
 * 9.11.4.2    5GSM cause
 */

const value_string nas_5gs_sm_cause_vals[] = {
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
const field_meta hf_sm_cause = {
    "5GSM cause",
    "nas_5gs.sm.5gsm_cause",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_cause_vals),
    nullptr,
    nullptr,
    0x0,
};
int sm::dissect_sm_cause(dissector d, context* ctx) {
    uint32_t cause = (uint32_t) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_cause, enc::be);

    return 1;
}

int sm::dissect_ext_pco(dissector d, context* ctx) {
    bug("no dissect\n");
    return d.length;
}

int sm::dissect_eap_msg(dissector d, context* ctx) {
    return nas::dissect_eap_msg(d, ctx);
}
// *     9.11.4.13    QoS rules

static true_false_string tfs_nas_5gs_sm_dqr = {
    "The QoS rule is the default QoS rule",
    "The QoS rule is not the default QoS rule",
};

static const value_string nas_5gs_rule_operation_code_values[] = {
    {0x0, "Reserved"},
    {0x1, "Create new QoS rule"},
    {0x2, "Delete existing QoS rule"},
    {0x3, "Modify existing QoS rule and add packet filters"},
    {0x4, "Modify existing QoS rule and replace packet filters"},
    {0x5, "Modify existing QoS rule and delete packet filters"},
    {0x6, "Modify existing QoS rule without modifying packet filters"},
    {0x7, "Reserved"},
    {0, nullptr},
};

static const value_string nas_5gs_sm_pf_type_values[] = {
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

static const value_string nas_5gs_sm_pkt_flt_dir_values[] = {
    {0x00, "Reserved"},
    {0x01, "Downlink only"},
    {0x02, "Uplink only"},
    {0x03, "Bidirectional"},
    {0, nullptr},
};

static const value_string nas_5gs_rule_param_cont[] = {
    {0x0, "Reserved"},
    {0x01, "5QI 1"},
    {0x02, "5QI 2"},
    {0x03, "5QI 3"},
    {0x04, "5QI 4"},
    {0x05, "5QI 5"},
    {0x06, "5QI 6"},
    {0x07, "5QI 7"},
    {0x08, "5QI 8"},
    {0x09, "5QI 9"},
    {0, nullptr},
};

const field_meta hf_sm_dqr = {
    "DQR",
    "nas_5gs.sm.dqr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_sm_dqr),
    nullptr,
    0x10,
};
const field_meta hf_sm_rop = {
    "Rule operation code",
    "nas_5gs.sm.rop",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_rule_operation_code_values),
    nullptr,
    nullptr,
    0xe0,
};
const field_meta hf_sm_nof_pkt_filters = {
    "Number of packet filters",
    "nas_5gs.sm.nof_pkt_filters",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};

const field_meta hf_sm_qfi = {
    "Qos flow identifier",
    "nas_5gs.sm.qfi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x3f,
};

const field_meta hf_sm_qos_rule_id = {
    "QoS rule identifier",
    "nas_5gs.sm.qos_rule_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_sm_length = {
    "Length",
    "nas_5gs.sm.length",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_sm_pkt_flt_id = {
    "Packet filter identifier",
    "nas_5gs.sm.pkt_flt_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0f,
};
const field_meta hf_sm_pkt_flt_dir = {
    "Packet filter direction",
    "nas_5gs.sm.pkt_flt_dir",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_pkt_flt_dir_values),
    nullptr,
    nullptr,
    0x30,
};
const field_meta hf_sm_pf_len = {
    "Length",
    "nas_5gs.sm.pf_len",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_sm_pf_type = {
    "Packet filter component type",
    "nas_5gs.sm.pf_type",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_pf_type_values),
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_pdu_addr_ipv4 = {
    "PDU address information",
    "nas_5gs.sm.pdu_addr_inf_ipv4",
    ft::ft_uint32, // FT_IPv4,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pdu_ipv4_mask = {
    "IPv4 address mask",
    "nas_5gs.ipv4_address_mask",
    ft::ft_uint32,
    fd::ipv4,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pid_next_hd = {
    "Protocol identifier/Next header type",
    "nas_5gs.protocol_identifier_or_next_hd",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0,
};
const field_meta hf_single_port_type = {
    "Port number",
    "nas_5gs.port_type",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_sm_qos_rule_precedence = {
    "QoS rule precedence",
    "nas_5gs.sm.qos_rule_precedence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

int dissect_packet_filter(dissector d, int pf_type, context* ctx) {
    auto len = d.length;
    switch (pf_type) {
    case 1: {
        /* Match-all type
         * . If the "match-all type" packet filter component is
         * present in the packet filter, no other packet filter
         * component shall be present in the packet filter and the
         * length of the packet filter contents field shall be set
         * to one.
         */
        len = 0;
    } break;
    case 16:
        /* For "IPv4 remote address type", the packet filter
         * component value field shall be encoded as a sequence of
         * a four octet IPv4 address field and a four octet IPv4
         * address mask field. The IPv4 address field shall be
         * transmitted first.
         */

    case 17: {
        /* For "IPv4 local address type", the packet filter
         * component value field shall be encoded as defined for
         * "IPv4 remote address type"
         */
        d.add_item(4, &hf_pdu_addr_ipv4, enc::be);
        d.step(4);
        d.add_item(4, &hf_pdu_ipv4_mask, enc::be);
        d.step(4);
        len = 8;
    } break;
    case 48: {
        d.add_item(1, &hf_pid_next_hd, enc::be);
        d.step(1);
        len = 1;
    } break;
    case 64: { /* Single local port type */
        d.add_item(2, &hf_single_port_type, enc::be);
        d.step(2);
        len = 2;
    } break;
    case 80: { /* Single remote port type */
        d.add_item(2, &hf_single_port_type, enc::be);
        d.step(2);
        len = 2;
    } break;
    default:
        d.step(d.length);
    }
    return len;
}
int dissect_packet_filters(dissector d, int rop, context* ctx) {
    auto start = d.offset;
    /* "create new QoS rule", or "modify existing QoS rule and add packet
     * filters" or "modify existing QoS rule and replace packet filters"
     */
    /* 0    0    Packet filter direction 1    Packet filter identifier 1*/
    d.add_item(1, &hf_sm_pkt_flt_dir, enc::be);
    d.add_item(1, &hf_sm_pkt_flt_id, enc::be);
    d.step(1);

    /* Length of packet filter contents */
    auto pfclen = (int) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_pf_len, enc::be);
    d.step(1);

    auto k       = 1;

    /* Packet filter contents */
    while (pfclen > 0) {
        auto start = d.offset;
        auto subtree = d.tree->add_subtree(
            d.pinfo, d.tvb, d.offset, -1, "Packet filter component %u", k);
        use_tree ut(d, subtree);
        /* Each packet filter component shall be encoded as a sequence of a
         * one octet packet filter component type identifier and a fixed
         * length packet filter component value field. The packet filter
         * component type identifier shall be transmitted first.
         */
        auto pf_type = d.tvb->uint8(d.offset);
        d.add_item(1, &hf_sm_pf_type, enc::be);
        d.step(1);
        /* Packet filter length contains the length of component type and
         * content */

        auto consumed = dissect_packet_filter(d.slice(pfclen - 1), pf_type, ctx);
        d.step(consumed);
        subtree->set_length(d.offset - start);

        ++k;
    } // while(fclen)

    return d.offset - start;
}
int sm::dissect_qos_rules(dissector d, context* ctx){
    auto                     len             = d.length;
    static const field_meta* pkt_flt_flags[] = {
        &hf_sm_rop,
        &hf_sm_dqr,
        &hf_sm_nof_pkt_filters,
        nullptr,
    };
    auto i = 1;
    while (d.offset > 0) {
        /* QoS Rule */
        auto subtree =
            d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "QoS rule %u", i);
        use_tree ut(d, subtree);

        /* QoS rule identifier Octet 4*/
        auto rule_id = d.tvb->uint8(d.offset);
        d.add_item(1, &hf_sm_qos_rule_id, enc::be);
        d.step(1);

        /* Length of QoS rule Octet 5 - 6*/
        auto length = (int) d.tvb->ntohs(d.offset);
        d.add_item(2, &hf_sm_length, enc::be);
        d.step(2);

        subtree->set_length(length + 3);

        /* Rule operation code    DQR bit    Number of packet filters */
        auto n_filters = d.tvb->uint8(d.offset);
        auto rop       = n_filters >> 5;
        n_filters      = n_filters & 0x0f;
        d.add_bits(pkt_flt_flags);
        d.step(1);

        /* For the "delete existing QoS rule" operation and for the "modify existing QoS
         * rule without modifying packet filters" operation, the number of packet filters
         * shall be coded as 0.
         */
        if (rop == 0 || rop == 7) {
            // reserved
            ++i;
            d.step(length - 1);
            continue;
        }
        if (rop == 2 || rop == 6) {
            if (n_filters != 0) {
                d.step(length - 1);
                ++i;
                continue;
            }
        }
        /* Packet filter list */
        auto j = 1;
        while (n_filters > 0) {
            auto subtree =
                d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Packet filter %u", j);
            use_tree ut(d, subtree);
            if (rop == 5) {
                /* modify existing QoS rule and delete packet filters */
                /* 0    0    0    0    Packet filter identifier x*/
                d.add_item(1, &hf_sm_pkt_flt_id, enc::be);
                d.step(1);
            } else {
                auto consumed = dissect_packet_filters(d, rop, ctx);
                d.step(consumed);
            }
        }
        /* QoS rule precedence (octet z+1)
         * For the "delete existing QoS rule" operation, the QoS rule precedence value
         * field shall not be included. For the "create new QoS rule" operation, the
         * QoS rule precedence value field shall be included.
         */
        if (rop != 2) { /* Delete existing QoS rule */
            d.add_item(1, &hf_sm_qos_rule_precedence, enc::be);
            d.step(1);
        }
        /* QoS flow identifier (QFI) (bits 6 to 1 of octet z+2)
         * For the "delete existing QoS rule" operation, the QoS flow identifier value
         * field shall not be included. For the "create new QoS rule" operation, the
         * QoS flow identifier value field shall be included.
         */
        /* Segregation bit (bit 7 of octet z+2) */
        d.add_item(1, &hf_sm_qfi, enc::be);
        d.step(1);

        ++i;
    } // while(d.offset)
    return len;
}
int sm::dissect_authorized_qos_rules(dissector d, context* ctx) {
    return dissect_qos_rules(d, ctx);
}

/*
 *     9.11.4.8 Mapped EPS bearer contexts
 */
static const value_string nas_5gs_sm_mapd_eps_b_cont_opt_code_vals[] = {
    {0x0, "Reserved"},
    {0x01, "Create new EPS bearer"},
    {0x02, "Delete existing EPS bearer"},
    {0x03, "Modify existing EPS bearer"},
    {0, nullptr},
};

static const value_string nas_5gs_sm_mapd_eps_b_cont_DEB_vals[] = {
    {0x0, "the EPS bearer is not the default EPS bearer."},
    {0x01, "the EPS bearer is the default EPS bearer"},
    {0, nullptr},
};

static const value_string nas_5gs_sm_mapd_eps_b_cont_E_vals[] = {
    {0x0, "parameters list is not included"},
    {0x01, "parameters list is included"},
    {0, nullptr},};

static const value_string nas_5gs_sm_mapd_eps_b_cont_E_Modify_vals[] = {
    {0x0, "previously provided parameters list extension"},
    {0x01, "previously provided parameters list replacement"},
    {0, nullptr},};

static const value_string nas_5gs_sm_mapd_eps_b_cont_param_id_vals[] = {
    {0x01, "Mapped EPS QoS parameters"},
    {0x02, "Mapped extended EPS QoS parameters"},
    {0x03, "Traffic flow template"},
    {0x04, "APN-AMBR"},
    {0x05, "extended APN-AMBR"},
    {0, nullptr},
};

const field_meta hf_sm_mapd_eps_b_cont_opt_code = {
    "Operation code",
    "nas_5gs.sm.mapd_eps_b_cont_opt_code",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sm_mapd_eps_b_cont_opt_code_vals,nullptr,nullptr,
    0xc0,
};
const field_meta hf_sm_mapd_eps_b_cont_deb = {
    "DEB bit",
    "nas_5gs.sm.mapd_eps_b_cont_DEB",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sm_mapd_eps_b_cont_DEB_vals,nullptr,nullptr,
    0x20,
};
const field_meta hf_sm_mapd_eps_b_cont_e = {
    "E bit",
    "nas_5gs.sm.mapd_eps_b_cont_E",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sm_mapd_eps_b_cont_E_vals,nullptr,nullptr,
    0x10,
};
const field_meta hf_sm_mapd_eps_b_cont_num_eps_parms = {
    "Number of EPS parameters",
    "nas_5gs.sm.mapd_eps_b_cont_num_eps_parms",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x0f,
};
const field_meta hf_sm_mapd_eps_b_cont_e_mod         = {
    "E bit",
    "nas_5gs.sm.mapd_eps_b_cont_E_mod",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sm_mapd_eps_b_cont_E_Modify_vals,nullptr,nullptr,
    0x10,
};

const field_meta hf_sm_mapd_eps_b_cont_id = {
    "EPS bearer identity",
    "nas_5gs.sm.mapd_eps_b_cont_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0xf0,
};
const field_meta hf_sm_mapd_eps_b_cont_num_eps_param_id = {
    "EPS parameter identity",
    "nas_5gs.sm.mapd_eps_b_cont_param_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sm_mapd_eps_b_cont_param_id_vals,nullptr,nullptr,
    0x0,
};
const field_meta hf_sm_mapd_eps_b_cont_eps_param_cont = {
    "EPS parameter contents",
    "nas_5gs.sm.mapd_eps_b_cont_eps_param_cont",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

int dissect_eps_param(dissector d, int i, context* ctx){
    auto start = d.offset;
    auto subtree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "EPS parameter %u", i);
    use_tree ut(d, subtree);

    /* EPS parameter identifier */
    uint32_t param_id = (uint32_t) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_mapd_eps_b_cont_num_eps_param_id, enc::be);
    d.step(1);

    /*length of the EPS parameter contents field */
    int length = (int) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_length, enc::be);
    d.step(1);

    subtree->set_length(length+3);
    /*length of the EPS parameter contents field */
    switch(param_id){
    case 1: /* 01H (Mapped EPS QoS parameters) */
    case 2: /* 02H (Mapped extended EPS QoS parameters) */
    case 3: /* 03H (Traffic flow template)*/
    case 4: /* 04H (APN-AMBR) */
    case 5: /* 05H (extended APN-AMBR). */
    default:
        d.add_item(length, &hf_sm_mapd_eps_b_cont_eps_param_cont, enc::be);
        d.step(length);
    }
    return d.offset - start;
}
int sm::dissect_mapped_eps_b_cont(dissector d, context* ctx) {
    static const field_meta* mapd_eps_b_cont_flags[] = {
        &hf_sm_mapd_eps_b_cont_opt_code,
        &hf_sm_mapd_eps_b_cont_deb,
        &hf_sm_mapd_eps_b_cont_e,
        &hf_sm_mapd_eps_b_cont_num_eps_parms,
        nullptr,
    };

    static const field_meta* mapd_eps_b_cont_flags_modify[] = {
        &hf_sm_mapd_eps_b_cont_opt_code,
        &hf_sm_mapd_eps_b_cont_deb,
        &hf_sm_mapd_eps_b_cont_e_mod,
        &hf_sm_mapd_eps_b_cont_num_eps_parms,
        nullptr,
    };
    auto n = 1;
    /* The IE contains a number of Mapped EPS bearer context */
    while(d.length>0){
        /* Figure 9.11.4.5.2: Mapped EPS bearer context */
        auto subtree = d.tree->add_subtree(
            d.pinfo, d.tvb, d.offset, -1, "Mapped EPS bearer context %u", n);
        use_tree ut(d, subtree);

        /* EPS bearer identity */
        d.add_item(1, &hf_sm_mapd_eps_b_cont_id, enc::be);
        d.step(1);

        /* Length of Mapped EPS bearer context*/
        int length = (int) d.tvb->ntohs(d.offset);
        d.add_item(2, &hf_sm_length, enc::be);
        d.step(2);

        /*     8   7      6    5   4  3  2  1          */
        /* operation code | DEB |  E | number of EPS params     */
        subtree->set_length(length + 3);

        auto nep = d.tvb->uint8(d.offset);
        auto opt_code = nep&0xc0;
        nep           = nep & 0x0f;

        /* operation code = 3 Modify existing EPS bearer */
        if (opt_code == 3){
            d.add_bits(mapd_eps_b_cont_flags_modify);
        }else{
            d.add_bits(mapd_eps_b_cont_flags);
        }
        d.step(1);

        /* EPS parameters list */
        auto i = 1;
        while(nep>0){
            auto consumed = dissect_eps_param(d, i, ctx);
            d.step(consumed);
            --nep;
            ++i;
        }
        ++n;
    }
    return d.length;
}

int sm::dissect_backoff_gprs_timer3(dissector d, context* ctx) {
    bug("no dissect\n");
    return d.length;
}

const true_false_string tfs_supported_not_supported = {"Supported", "Not supported"};

const field_meta hf_sm_rqos_b0 = {
    "Reflective QoS(RqoS)",
    "nas_5gs.sm.rqos",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    (&tfs_supported_not_supported),
    nullptr,
    0x01,
};
/*
 *       9.11.4.1    5GSM capability
 */
int sm::dissect_sm_cap(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b7,
        &hf_spare_b6,
        &hf_spare_b5,
        &hf_spare_b4,
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_spare_b1,
        &hf_sm_rqos_b0,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

//  *     9.11.4.9    Maximum number of supported packet filters
int sm::dissect_max_num_sup_kpt_flt(dissector d, context* ctx) {
    bug("no dissect\n");
    return d.length;
}

//  *      9.11.4.14    Session-AMBR
extern const value_string sm::nas_5gs_sm_unit_for_session_ambr_values[] = {
    {0x00, "value is not used"},
    {0x01, "value is incremented in multiples of 1 Kbps"},
    {0x02, "value is incremented in multiples of 4 Kbps"},
    {0x03, "value is incremented in multiples of 16 Kbps"},
    {0x04, "value is incremented in multiples of 64 Kbps"},
    {0x05, "value is incremented in multiples of 256 kbps"},
    {0x06, "value is incremented in multiples of 1 Mbps"},
    {0x07, "value is incremented in multiples of 4 Mbps"},
    {0x08, "value is incremented in multiples of 16 Mbps"},
    {0x09, "value is incremented in multiples of 64 Mbps"},
    {0x0a, "value is incremented in multiples of 256 Mbps"},
    {0x0b, "value is incremented in multiples of 1 Gbps"},
    {0x0c, "value is incremented in multiples of 4 Gbps"},
    {0x0d, "value is incremented in multiples of 16 Gbps"},
    {0x0e, "value is incremented in multiples of 64 Gbps"},
    {0x0f, "value is incremented in multiples of 256 Gbps"},
    {0x10, "value is incremented in multiples of 1 Tbps"},
    {0x11, "value is incremented in multiples of 4 Tbps"},
    {0x12, "value is incremented in multiples of 16 Tbps"},
    {0x13, "value is incremented in multiples of 64 Tbps"},
    {0x14, "value is incremented in multiples of 256 Tbps"},
    {0x15, "value is incremented in multiples of 1 Pbps"},
    {0x16, "value is incremented in multiples of 4 Pbps"},
    {0x17, "value is incremented in multiples of 16 Pbps"},
    {0x18, "value is incremented in multiples of 64 Pbps"},
    {0x19, "value is incremented in multiples of 256 Pbps"},
    {0, nullptr},
};

uint32_t sm::get_ext_ambr_unit(uint32_t unit, const char** unit_str) {
    uint32_t mult = 1;

    if (unit == 0) {
        *unit_str = "Unit value 0, Illegal";
        return mult;
    }
    unit = unit - 1;

    if (unit <= 0x05) {
        mult      = 1 << (2 * unit); // pow4(guint32, unit);
        *unit_str = "Kbps";
    } else if (unit <= 0x0a) {
        mult = 1 << (2 * (unit - 0x05)); // pow4(guint32, unit - 0x05);
        *unit_str = "Mbps";
    } else if (unit <= 0x0e) {
        mult      = 1 << (2 * (unit - 0x07)); // pow4(guint32, unit - 0x07);
        *unit_str = "Gbps";
    } else if (unit <= 0x14) {
        mult = 1 << (2 * (unit - 0x0c)); // pow4(guint32, unit - 0x0c);
        *unit_str = "Tbps";
    } else if (unit <= 0x19) {
        mult = 1 << (2 * (unit - 0x11)); // pow4(guint32, unit - 0x11);
        *unit_str = "Pbps";
    } else {
        mult      = 256;
        *unit_str = "Pbps";
    }
    return mult;
}


int sm::dissect_ses_ambr(dissector d, context* ctx) {
    auto len = d.length;

    /* Unit for Session-AMBR for downlink */
    auto unit = (int) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_ses_ambr_dl_unit, enc::be);
    d.step(1);

    const char* unit_str = "";
    /* Session-AMBR for downlink (octets 4 and 5) */
    auto mult = get_ext_ambr_unit(unit, &unit_str);
    auto ambr_val = (uint32_t) d.tvb->ntohs(d.offset);
    auto item = d.add_item(2, &hf_sm_ses_ambr_dl, enc::none);
    item->set_string(formats("%u %s (%u)", ambr_val * mult, unit_str, ambr_val));
    d.step(2);

    unit = (int) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_ses_ambr_ul_unit, enc::be);
    d.step(1);

    mult = get_ext_ambr_unit(unit, &unit_str);
    ambr_val = (uint32_t) d.tvb->ntohs(d.offset);
    item = d.add_item(2, &hf_sm_ses_ambr_ul, enc::none);
    item->set_string(formats("%u %s (%u)", ambr_val * mult, unit_str, ambr_val));

    return len;
}

int sm::dissect_rq_gprs_timer(dissector d, context* ctx) {
    bug("no dissect\n");
    return d.length;
}

/*
 * 9.11.4.3 Always-on PDU session indication
 */

int sm::dissect_always_on_pdu_ses_ind(dissector d, context* ctx) {
    bug("no dissect\n");
    return d.length;
}

// * 9.11.4.7 Integrity protection maximum data rate
static const value_string nas_5gs_sm_int_prot_max_data_rate_vals[] = {
    {0x0, "64 kbps"},
    {0xff, "Full data rate"},
    {0, nullptr},
};

const field_meta hf_sm_int_prot_max_data_rate_ul = {
    "Integrity protection maximum data rate for uplink",
    "nas_5gs.sm.int_prot_max_data_rate_ul",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_int_prot_max_data_rate_vals),
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_sm_int_prot_max_data_rate_dl = {
    "Integrity protection maximum data rate for downlink",
    "nas_5gs.sm.int_prot_max_data_rate_dl",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_int_prot_max_data_rate_vals),
    nullptr,
    nullptr,
    0x0,
};

//  * 9.11.4.7 Integrity protection maximum data rate
int sm::dissect_int_prot_max_data_rate(dissector d, context* ctx) {
    /* Maximum data rate per UE for user-plane integrity protection for uplink */
    d.add_item(1, &hf_sm_int_prot_max_data_rate_ul, enc::be);
    d.step(1);

    /* Maximum data rate per UE for user-plane integrity protection for downlink */
    d.add_item(1, &hf_sm_int_prot_max_data_rate_dl, enc::be);
    d.step(1);

    return 2;
}


const field_meta hf_sm_all_ssc_mode_b2 = {
    "SSC mode 3",
    "nas_5gs.sm.all_ssc_mode_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x04,
};
const field_meta hf_sm_all_ssc_mode_b1 = {
    "SSC mode 2",
    "nas_5gs.sm.all_ssc_mode_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x02,
};
const field_meta hf_sm_all_ssc_mode_b0 = {
    "SSC mode 1",
    "nas_5gs.sm.all_ssc_mode_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x01,
};

/*
 * 9.11.4.5    Allowed SSC mode
 */
int sm::dissect_allowed_ssc_mode(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b3,
        &hf_sm_all_ssc_mode_b2,
        &hf_sm_all_ssc_mode_b1,
        &hf_sm_all_ssc_mode_b0,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

/*
 *      9.11.4.16    SSC mode
 */

static const value_string nas_5gs_sc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0, nullptr},
};

const field_meta hf_sm_sc_mode = {
    "SSC mode",
    "nas_5gs.sm.sc_mode",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sc_mode_values),
    nullptr,
    nullptr,
    0x0f,
};
int sm::dissect_ssc_mode(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_sc_mode, enc::be);
    return 1;
}
