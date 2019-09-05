#include "../dissect_sm_msg.hh"


// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
extern const element_meta sm::authorized_qos_flow_des = {
    0x79,
    "QoS flow descriptions - Authorized",
    dissect_authorized_qos_flow_des,
    nullptr,
};

const field_meta sm::hf_sm_qfi = {
    "Qos flow identifier",
    "nas_5gs.sm.qfi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x3f,
};


/* 9.11.4.12 QoS flow descriptions */
const value_string nas_5gs_sm_qos_des_flow_opt_code_vals[] = {
    {0x00, "Reserved"},
    {0x01, "Create new QoS flow description"},
    {0x02, "Delete existing QoS flow description"},
    {0x03, "Modify existing QoS flow description"},
    {0, nullptr},
};

const field_meta sm::hf_sm_qos_des_flow_opt_code = {
    "Operation code",
    "nas_5gs.sm.hf_nas_5gs_sm_qos_des_flow_opt_code",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_sm_qos_des_flow_opt_code_vals),
    nullptr,
    nullptr,
    0xe0,
};

int sm::dissect_qos_param(dissector d, int j, context* ctx) {
    const use_context uc(ctx, "qos-param", d, -1);

    /* Parameter list */
    auto     subtree = d.add_item(-1, "Parameter %u", j);
    use_tree ut(d, subtree);

    auto start = d.offset;

    /* Parameter identifier */
    uint32_t param_id = (uint32_t) d.uint8();
    d.add_item(1, &hf_sm_param_id, enc::be);
    d.step(1);

    /* Length of parameter contents */
    int param_len = (int) d.uint8();
    d.add_item(1, &hf_sm_param_len, enc::be);
    d.step(1);

    /*parameter content*/
    switch (param_id) {
    case 0x01: /* 01H (5QI)*/
        d.add_item(param_len, &hf_sm_pal_cont, enc::be);
        d.step(param_len);
        break;
        /* 02H (GFBR uplink);*/
    case 0x02:
    case 0x04: { //  04H (MFBR uplink)
        /* Unit for Session-AMBR for uplink */
        uint32_t unit = (uint32_t) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_sm_ses_ambr_ul_unit, enc::be);
        d.step(1);

        /* Session-AMBR for downlink */
        auto ambr_val = d.tvb->ntohs(d.offset);
        auto item     = d.add_item(param_len - 1, &hf_sm_ses_ambr_ul, enc::be);
        item->set_string(ambr_string(ambr_val, unit));
        d.step(param_len - 1);
    } break;

    case 0x03: /* 03H (GFBR downlink); 05H (MFBR downlink);*/
    case 0x05: {
        /* Unit for Session-AMBR for uplink */
        uint32_t unit = (uint32_t) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_sm_ses_ambr_dl_unit, enc::be);
        d.step(1);

        /* Session-AMBR for downlink*/
        auto ambr_val = d.tvb->ntohs(d.offset);
        auto item     = d.add_item(param_len - 1, &hf_sm_ses_ambr_dl, enc::be);
        item->set_string(ambr_string(ambr_val, unit));
        d.step(param_len - 1);
    } break;
    case 06: // averaging window; and
        d.add_item(2, &hf_averaging_wind, enc::be);
        d.step(2);
        break;
    case 07: // EPS bearer identity
        // coded as specified in subclause 9.3.2 of 3GPP TS 24.301 [15]
        d.add_item(1, &hf_eps_bearer_identity, enc::be);
        d.step(1);
        break;
    default:
        d.add_item(param_len, &hf_sm_pal_cont, enc::be);
        d.step(param_len);
        break;
    }

    d.tree->set_length(d.offset - start);
    return d.offset - start;
}

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
int sm::dissect_authorized_qos_flow_des(dissector d, context* ctx) {
    const use_context uc(ctx, "authorized-qos-flow-desc", d, 0);   

    static const field_meta* param_flags[] = {
        &hf_sm_e,
        &hf_sm_nof_params,
        nullptr,
    };

    auto i = 1;
    while (d.length > 0) {
        /* QoS fow description */
        auto     subtree = d.add_item(-1, "QoS flow description %u", i);
        use_tree ut(d, subtree);

        /* 0 0 QFI */
        d.add_item(1, &hf_sm_qfi, enc::be);
        d.step(1);

        /* Operation code */
        d.add_item(1, &hf_sm_qos_des_flow_opt_code, enc::be);
        d.step(1);

        /* 0 Spare    E    Number of parameters */
        auto num_param = d.uint8() & 0x3fu;
        d.add_bits(param_flags);
        d.step(1);

        auto j = 1;
        while (num_param > 0) {
            auto consumed = dissect_qos_param(d, j, ctx);
            d.step(consumed);
            ++j;
            --num_param;
        }

        i++;
    }
    return d.offset - uc.offset;
}
