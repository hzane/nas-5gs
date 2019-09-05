#include "dissect_sm_msg.hh"
#include "dissect_nas5g.hh"
#include "ts24007.hh"
#include "common/common.hh"

using namespace cmn;
using namespace nas;
using namespace sm;

/* 8.3 5GS session management messages */

/*
 * 8.3.6 PDU session authentication result
 */
int sm::dissect_pdu_ses_auth_res(dissector d, context* ctx) {
    auto start = d.offset;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*EAP message    EAP message 9.11.2.2    M    LV-E    6-1502 */
    // ELEM_MAND_LV_E(,  DE_NAS_5GS_CMN_EAP_MESSAGE,  );
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

// 5GSM cause 9.11.4.2
int sm::dissect_sm_cause(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_cause, enc::be);

    return 1;
}
const field_meta hf_gsma_sm_ext = {
    "Extension",
    "nas_5gs.gsm.sm.ext",
    ft::ft_uint8,
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

// Extended protocol configuration options  9.11.4.6
int sm::dissect_ext_pco(dissector d, context* ctx) {
    // See subclause 10.5.6.3A in 3GPP TS 24.008
    auto len = d.length;
    auto oct = d.uint8();

    /* 1 ext 0 0 0 0 Spare  Configuration protocol */
    d.add_item(1, &hf_gsma_sm_ext, enc::be);
    d.add_item(1, &hf_gsma_conf_prot, enc::be);
    d.step(1);

    // DETAIL:

    return len;
}

// EAP message 9.11.2.2
int sm::dissect_eap_msg(dissector d, context* ctx) {
    return cmn::dissect_eap_msg(d, ctx);
}

/*The description and valid combinations of packet filter component type identifiers in a
 * packet filter are defined in 3GPP TS 23.501 [8].*/
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
    case 33: { // IPv6 remote address/prefix length type
    };
    case 35: { // IPv6 local address/prefix length type
        // d.add_item(16, &hf_pdu_addr_ipv6, enc::be);
        d.step(16);
        // d.add_item(1, &hf_pdu_addr_ipv6_prefix, enc::be);
        d.step(1);
    }break;
    case 48: { // Protocol identifier/Next header type
        d.add_item(1, &hf_pid_next_hd, enc::be);
        d.step(1);
        len = 1;
    } break;
    case 64: { /* Single local port type */
        d.add_item(2, &hf_single_port_type, enc::be);
        d.step(2);
        len = 2;
    } break;
    case 0x51: { // Remote port range type
        // the packet filter component value field shall be encoded as a sequence of a two
        // octet port range low limit field and a two octet port range high limit field.
        // The port range low limit field shall be transmitted first
        d.step(4);
    }break;
    case 80: { /* Single remote port type */
    } ;
    case 0x41: { // Local port range type
        d.add_item(2, &hf_single_port_type, enc::be);
        d.step(2);
        len = 2;
    }; break;
    case 0x60: { // Security parameter index type
        // For "security parameter index", the packet filter component value field shall
        // be encoded as four octets which specify the IPSec security parameter index
        d.step(4);
    }break;
    case 0x70: { // Type of service/Traffic class type
        // For "type of service/traffic class type", the packet filter component value
        // field shall be encoded as a sequence of a one octet type-of-service/traffic
        // class field and a one octet type-of-service/traffic class mask field. The
        // type-of-service/traffic class field shall be transmitted first.
        d.step(2);
    }break;
    default:
        d.step(d.length);
    }
    return len;
}

// Figure 9.11.4.13.4 Packet filter list when the rule operation is "create new QoS rule",
// or "modify existing QoS rule and add packet filters" or "modify existing QoS rule and
// replace all packet filters"
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
    auto pfclen = (int) d.uint8();
    d.add_item(1, &hf_sm_pf_len, enc::be);
    d.step(1);

    d.step(pfclen);
    pfclen = 0; // skip dissect packet filter contents
    // TODO: detail
    auto k       = 1;
    /* Packet filter contents */
    while (pfclen > 0) {
        auto start = d.offset;
        auto subtree = d.add_item( -1, "Packet filter component %u", k);
        use_tree ut(d, subtree);
        /* Each packet filter component shall be encoded as a sequence of a
         * one octet packet filter component type identifier and a fixed
         * length packet filter component value field. The packet filter
         * component type identifier shall be transmitted first.
         */
        auto pf_type = d.uint8();
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
const true_false_string tfs_segregation = {
    "Segregation requested",
    "Segregation not requested",
};
const field_meta hf_segregation = {
    "Segregation",
    "nas_5gs.sm.qos_rule.segregation",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_segregation,
    nullptr,
    0x40u,
};
// Authorized QoS rules QoS rules 9.11.4.13
int sm::dissect_qos_rules(dissector d, context* ctx){
    use_context              uc(ctx, "authorized-qos-rules", d);
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
        auto     subtree = d.add_item(-1, "QoS rule %u", i);
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
        auto rop       = n_filters >> 5u;
        n_filters      = n_filters & 0x0fu;
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
        // 6 Modify existing QoS rule without modifying packet filters
        if (rop == 2 || rop == 6) { // 2 Delete existing QoS rule
            if (n_filters != 0) {
                diag("the number of packet filters shall be coded as 0\n");
                d.step(length - 1);
                ++i;
                continue;
            }
        }
        /* Packet filter list */
        auto j = 1;
        while (n_filters > 0) {
            auto     subtree = d.add_item(-1, "Packet filter %u", j);
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
        d.add_item(1, &hf_segregation, enc::be);
        d.step(1);

        ++i;
    } // while(d.offset)
    return len;
}

// Authorized QoS rules QoS rules 9.11.4.13
int sm::dissect_authorized_qos_rules(dissector d, context* ctx) {
    return dissect_qos_rules(d, ctx);
}

/* 9.11.4.8 Mapped EPS bearer contexts */

int dissect_eps_param(dissector d, int i, context* ctx){
    auto start = d.offset;
    auto     subtree = d.add_item(-1, "EPS parameter %u", i);
    use_tree ut(d, subtree);

    /* EPS parameter identifier */
    uint32_t param_id = (uint32_t) d.uint8();
    d.add_item(1, &hf_sm_mapd_eps_b_cont_num_eps_param_id, enc::be);
    d.step(1);

    /*length of the EPS parameter contents field */
    int length = (int) d.uint8();
    d.add_item(1, &hf_sm_length, enc::be);
    d.step(1);

    subtree->set_length(length+2);
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

// Mapped EPS  bearer contexts     9.11.4.8
int sm::dissect_mapped_eps_b_cont(dissector d, context* ctx) {
    auto len = d.length;

    static const field_meta* mapd_eps_b_cont_flags[] = {
        &hf_sm_mapd_eps_b_cont_opt_code,
        &hf_spare_b5,
        &hf_sm_mapd_eps_b_cont_e,
        &hf_sm_mapd_eps_b_cont_num_eps_parms,
        nullptr,
    };

    static const field_meta* mapd_eps_b_cont_flags_modify[] = {
        &hf_sm_mapd_eps_b_cont_opt_code,
        &hf_spare_b5,
        &hf_sm_mapd_eps_b_cont_e_mod,
        &hf_sm_mapd_eps_b_cont_num_eps_parms,
        nullptr,
    };
    auto n = 1;
    /* The IE contains a number of Mapped EPS bearer context */
    while(d.length>0){
        /* Figure 9.11.4.5.2: Mapped EPS bearer context */
        auto subtree = d.add_item(-1, "Mapped EPS bearer context %u", n);
        use_tree ut(d, subtree);

        /* EPS bearer identity */
        d.add_item(1, &hf_sm_mapd_eps_b_cont_id, enc::be);
        d.step(1);

        /* Length of Mapped EPS bearer context*/
        int length = (int) d.ntohs();
        d.add_item(2, &hf_sm_length, enc::be);
        d.step(2);

        subtree->set_length(length + 3);
        /*     8   7      6    5   4  3  2  1          */
        /* operation code | spare |  E | number of EPS params     */

        auto nep = d.tvb->uint8(d.offset);
        auto opt_code = (nep & 0xc0u) >> 6u;
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
    return len;
}

/*  9.11.4.1    5GSM capability */
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

const field_meta hf_max_supported_packet_filters = {
    "Maximum number of supported packet filters",
    "nas_5gs.max_n_supported_filters",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_max_supported_packet_filters_c = {
    "Maximum number of supported packet filters(continued)",
    "nas_5gs.max_n_supported_filters",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0xe0u,
};

//  *     9.11.4.9    Maximum number of supported packet filters
int sm::dissect_max_num_sup_kpt_flt(dissector d, context* ctx) {
    d.add_item(1, &hf_max_supported_packet_filters, enc::be);
    d.step(1);
    d.add_item(1, &hf_max_supported_packet_filters_c, enc::be);
    d.step(1);

    return 2;
}

// 9.11.4.14    Session-AMBR
int sm::dissect_ses_ambr(dissector d, context* ctx) {
    auto len = d.length;

    /* Unit for Session-AMBR for downlink */
    auto unit = (int) d.uint8();
    d.add_item(1, &hf_sm_ses_ambr_dl_unit, enc::be);
    d.step(1);

    // const char* unit_str = "";
    /* Session-AMBR for downlink (octets 4 and 5) */
    auto ambr_val = (uint32_t) d.ntohs();

    auto item = d.add_item(2, &hf_sm_ses_ambr_dl, enc::none);
    item->set_string(ambr_string(ambr_val, unit));
    d.step(2);

    unit = (int) d.uint8();
    item = d.add_item(1, &hf_sm_ses_ambr_ul_unit, enc::be);
    d.step(1);

    ambr_val = (uint32_t) d.ntohs();
    item = d.add_item(2, &hf_sm_ses_ambr_ul, enc::none);
    item->set_string(ambr_string(ambr_val, unit));
    d.step(2);

    return len;
}

const true_false_string tfs_pdu_always_on_ses_id_apsi = {
    "Always-on PDU session allowed",
    "Always-on PDU session not allowed"};

const field_meta hf_pdu_always_on_ses_ind = {
    "Always-on PDU session indication",
    "nas_5gs.sm.pdu.ses_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    &tfs_pdu_always_on_ses_id_apsi,
    nullptr,
    0x01,
};

/*  9.11.4.3 Always-on PDU session indication */
int sm::dissect_always_on_pdu_ses_ind(dissector d, context* ctx) {
    d.add_item(1, &hf_pdu_always_on_ses_ind, enc::be);
    return d.length;
}

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

/* 9.11.4.5    Allowed SSC mode */
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

/*  9.11.4.16    SSC mode */
int sm::dissect_ssc_mode(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_sc_mode, enc::be);
    return 1;
}

