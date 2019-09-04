#include "../dissect_nas5g.hh"
#include "../dissect_sm_msg.hh"
#include "../ts24007.hh"

namespace sm_pdu_ses_mod {
extern const element_meta authorized_qos_flow_des;
}

using namespace nas;
using namespace sm;

/*
 * 8.3.9 PDU session modification command
 */
int sm::pdu_ses_mod_cmd(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "pdu-session-modification-command");

    using namespace sm_pdu_ses_mod;
    /* Direction: network to UE */
    d.pinfo->dir = pi_dir::dl;

    /*59    5GSM cause    5GSM cause 9.11.4.2    O    TV    2*/
    // ELEM_OPT_TV(0x59, , DE_NAS_5GS_SM_5GSM_CAUSE, NULL);
    auto consumed = dissect_opt_elem_tv(nullptr, &sm_cause, d, ctx);
    d.step(consumed);

    /*2A    Session AMBR    Session-AMBR     9.11.4.14    O    TLV    8*/
    // ELEM_OPT_TLV(0x2A, , DE_NAS_5GS_SM_SESSION_AMBR, NULL);
    consumed = dissect_opt_elem_tlv(nullptr, &ses_ambr, d, ctx);
    d.step(consumed);

    /*56    RQ timer value    GPRS timer     9.11.4.3    O    TV    2*/
    // ELEM_OPT_TV(0x56, GSM_A_PDU_TYPE_GM, DE_GPRS_TIMER, " - PDU session release time");
    consumed = dissect_opt_elem_tv(nullptr, &rq_gprs_timer, d, ctx);
    d.step(consumed);

    /* 8-   Always-on PDU session indication    Always-on PDU session indication 9.11.4.3
     * O    TV    1 */
    // ELEM_OPT_TV_SHORT(  0x80, , DE_NAS_5GS_SM_ALWAYS_ON_PDU_SES_IND, NULL);
    consumed = dissect_opt_elem_tv_short(nullptr, &always_on_pdu_ses_ind, d, ctx);
    d.step(consumed);

    /*7A    Authorized QoS rules    QoS rules     9.11.4.6    O    TLV-E    3-65538*/
    // ELEM_OPT_TLV_E(  0x7A, , DE_NAS_5GS_SM_QOS_RULES, " - Authorized QoS rules");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_rules, d, ctx);
    d.step(consumed);

    /*75    Mapped EPS bearer contexts     Mapped EPS  bearer contexts     9.11.4.5    O
     * TLV-E    7-65538*/
    // ELEM_OPT_TLV_E(0x75, , DE_NAS_5GS_SM_MAPPED_EPS_B_CONT, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &mapped_eps_b_cont, d, ctx);
    d.step(consumed);

    /*79    Authorized QoS flow descriptions     QoS flow descriptions     9.11.4.12    O
     * TLV-E    6-65538*/
    // ELEM_OPT_TLV_E(  0x79, , DE_NAS_5GS_SM_QOS_FLOW_DES, " - Authorized");
    consumed = dissect_opt_elem_tlv_e(nullptr, &authorized_qos_flow_des, d, ctx);
    d.step(consumed);

    /*7B    Extended protocol configuration options    Extended protocol configuration
     * options     9.11.4.2    O    TLV-E    4-65538*/
    // ELEM_OPT_TLV_E(0x7B, NAS_PDU_TYPE_ESM, DE_ESM_EXT_PCO, NULL);
    consumed = dissect_opt_elem_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);

    return len;
}
namespace sm_pdu_ses_mod {
int dissect_authorized_qos_flow_des(dissector d, context* ctx);

extern const element_meta authorized_qos_flow_des = {
    0x79,
    "Authorized QoS flow descriptions",
    dissect_authorized_qos_flow_des,
    nullptr,
};

// 9.11.4.4 Always-on PDU session requested
int dissect_always_on_pdu_ses_req(dissector d, context* ctx) {
    diag("no dissect\n");
    return d.length;
}


/*
 *     9.11.4.13    QoS rules
 */

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
int dissect_requested_qos_rules(dissector d, context* ctx) {
    return dissect_qos_rules(d, ctx);
}

const field_meta hf_sm_e = {
    "E bit",
    "nas_5gs.sm.e",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x40,
};
const field_meta hf_sm_nof_params = {
    "Number of parameters",
    "nas_5gs.sm.nof_params",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x3f,
};
/*
 * 9.11.4.12 QoS flow descriptions
 */
static const value_string nas_5gs_sm_qos_des_flow_opt_code_vals[] = {
    {0x00, "Reserved"},
    {0x01, "Create new QoS flow description"},
    {0x02, "Delete existing QoS flow description"},
    {0x03, "Modify existing QoS flow description"},
    {0, nullptr},
};

static const value_string nas_5gs_sm_param_id_values[] = {
    {0x01, "5QI"},
    {0x02, "GFBR uplink"},
    {0x03, "GFBR downlink"},
    {0x04, "MFBR uplink"},
    {0x05, "MFBR downlink"},
    {0x06, "Averaging window"},
    {0x07, "EPS bearer identity"},
    {0, nullptr},
};
const field_meta hf_sm_param_id = {};
const field_meta hf_sm_param_len = {};
const field_meta hf_sm_pal_cont = {};

int dissect_qos(dissector d, int j, context* ctx) {
    /* Parameter list */
    auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "Parameter %u", j);
    use_tree ut(d, subtree);

    auto start = d.offset;

    /* Parameter identifier */
    uint32_t param_id = (uint32_t) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_param_id, enc::be);
    d.step(1);

    /* Length of parameter contents */
    int param_len = (int) d.tvb->uint8(d.offset);
    d.add_item(1, &hf_sm_param_len, enc::be);
    d.step(1);

    /*parameter content*/
    switch (param_id) {

    case 0x01:/* 01H (5QI)*/
        d.add_item(param_len, &hf_sm_pal_cont, enc::be);
        d.step(param_len);
        break;
        /* 02H (GFBR uplink); 04H (MFBR uplink);*/
    case 0x02:
    case 0x04: {
        /* Unit for Session-AMBR for uplink */
        uint32_t unit = (uint32_t) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_sm_ses_ambr_ul_unit, enc::be);
        d.step(1);

        /* Session-AMBR for downlink */
        auto        ambr_val = d.tvb->ntohs(d.offset);
        auto item = d.add_item(param_len - 1, &hf_sm_ses_ambr_ul, enc::be);
        item->set_string(ambr_string(ambr_val, unit));
        d.step(param_len - 1);
    } break;

    case 0x03:/* 03H (GFBR downlink); 05H (MFBR downlink);*/
    case 0x05:{
        /* Unit for Session-AMBR for uplink */
        uint32_t unit = (uint32_t) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_sm_ses_ambr_dl_unit, enc::be);
        d.step(1);

        /* Session-AMBR for downlink*/

        auto        ambr_val = d.tvb->ntohs(d.offset);
        auto item = d.add_item(param_len - 1, &hf_sm_ses_ambr_dl, enc::be);
        item->set_string(ambr_string(ambr_val, unit));
        d.step(param_len - 1);
    }
        break;
    default:
        d.add_item(param_len, &hf_sm_pal_cont, enc::be);
        d.step(param_len);
        break;
    }

    d.tree->set_length(d.offset - start);
    return d.offset - start;
}

const field_meta hf_sm_qfi = {
    "Qos flow identifier",
    "nas_5gs.sm.qfi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x3f,
};
const field_meta hf_sm_qos_des_flow_opt_code = {
    "Operation code",
    "nas_5gs.sm.hf_nas_5gs_sm_qos_des_flow_opt_code",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_qos_des_flow_opt_code_vals),
    nullptr,
    nullptr,
    0xe0,
};

int dissect_authorized_qos_flow_des(dissector d, context* ctx) {
    auto start = d.offset;

    static const field_meta* param_flags[] = {
        &hf_sm_e,
        &hf_sm_nof_params,
        nullptr,
    };

    auto i = 1;
    while(d.length>0){
        /* QoS fow description */
        auto subtree = d.tree->add_subtree(
            d.pinfo, d.tvb, d.offset, -1, "QoS flow description %u", i);
        use_tree ut(d, subtree);

        /* 0 0 QFI */
        d.add_item(1, &hf_sm_qfi, enc::be);
        d.step(1);

        /* Operation code */
        d.add_item(1, &hf_sm_qos_des_flow_opt_code, enc::be);
        d.step(1);

        /* 0 Spare    E    Number of parameters */
        auto num_param = d.tvb->uint8(d.offset);
        num_param = num_param & 0x3f;
        d.add_bits(param_flags);
        d.step(1);

        auto j = 1;
        while (num_param > 0) {
            auto consumed = dissect_qos(d, j, ctx);
            d.step(consumed);
            ++j;
            --num_param;
        }

        i++;
    }
    return d.offset - start;
}
} // namespace sm_pdu_ses_mod
