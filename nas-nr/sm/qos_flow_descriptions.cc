#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

extern const uint8_field hf_sm_qos_flow_identity = {
    "Qos flow identifier",
    0x3f,
};


/* 9.11.4.12 QoS flow descriptions op code*/
const value_string qos_flow_description_operation_code_values[] = {
    {0x00, "Reserved"},
    {0x01, "Create new QoS flow description"},
    {0x02, "Delete existing QoS flow description"},
    {0x03, "Modify existing QoS flow description"},
    {0, nullptr},
};

const tag_field hf_qos_flow_operation_code = {
    "Operation code",
    0xe0,
    qos_flow_description_operation_code_values,
};

const tag_field hf_sm_parameter_identifier = {
    "Parameter identifier",
    0x0,
    (const v_string[]){
        {0x01, "5QI"},
        {0x02, "GFBR uplink"},
        {0x03, "GFBR downlink"},
        {0x04, "MFBR uplink"},
        {0x05, "MFBR downlink"},
        {0x06, "Averaging window"},
        {0x07, "EPS bearer identity"},
        {0, nullptr},
    },
};

const tag_field hf_sm_parameters_content = {
    "Parameters content",
    0x0,
    (const v_string[]){
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
    },
};

extern const ambr_field hf_session_ambr_uplink;
extern const ambr_field hf_session_ambr_downlink;

const uint16_field hf_averaging_window = {
    "Average Window",
    0,
};

const uint8_field hf_eps_bearer_identity = {
    "EPS bearer identity",
    0,
};

int sm::dissect_qos_parameters(dissector d, int j, context* ctx) {
    const use_context uc(ctx, "qos-param", d, -1);

    /* Parameter list */
    const auto     subtree = d.add_item(-1, formats("Parameter %u", j));
    use_tree ut(d, subtree);

    /* Parameter identifier */
    const auto param_id = static_cast< uint32_t >(d.uint8());
    (void) d.add_item( &hf_sm_parameter_identifier);
    d.step(1);

    /* Length of parameter contents */
    const auto param_len = static_cast< int >(d.uint8());
    // d.add_item(1, &hf_sm_param_len);
    d.step(1);

    /*parameter content*/
    switch (param_id) {
    case 0x01: /* 01H (5QI)*/
        (void) d.add_item(&hf_sm_parameters_content, param_len);
        d.step(param_len);
        break;
        /* 02H (GFBR uplink);*/
    case 0x02:
    case 0x04:  //  04H (MFBR uplink)
        /* Unit for Session-AMBR for uplink */
        /* Session-AMBR for downlink */
        (void) d.add_item(&hf_session_ambr_uplink);
        d.step(3);
        break;

    case 0x03: /* 03H (GFBR downlink); 05H (MFBR downlink);*/
    case 0x05:
        /* Unit for Session-AMBR for uplink */
        /* Session-AMBR for downlink*/
        (void) d.add_item(&hf_session_ambr_downlink);
        d.step(3);
        break;
    case 06: // averaging window; and
        (void) d.add_item( &hf_averaging_window);
        d.step(2);
        break;
    case 07: // EPS bearer identity
        // coded as specified in subclause 9.3.2 of 3GPP TS 24.301 [15]
        (void) d.add_item( &hf_eps_bearer_identity);
        d.step(1);
        break;
    default:
        (void) d.add_item(&hf_sm_parameters_content, param_len);
        d.step(param_len);
        break;
    }

    d.tree->set_length(d.offset - uc.offset);
    return d.offset - uc.offset;
}


const bool_field hf_qos_flow_ebit = {
    "E bit",
    0x40,
};

const uint8_field hf_sm_parameters_number = {
    "Number of parameters",
    0x3f,
};

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
int sm::dissect_authorized_qos_flow_description(dissector d, context* ctx) {
    const use_context uc(ctx, "authorized-qos-flow-desc", d, 0);

    auto i = 1;
    while (d.length > 0) {
        /* QoS fow description */
        const auto subtree = d.add_item(-1, formats("QoS flow description %u", i++));
        use_tree   ut(d, subtree);

        /* 0 0 QFI */
        (void) d.add_item( &hf_sm_qos_flow_identity);
        d.step(1);

        /* Operation code */
        (void) d.add_item( &hf_qos_flow_operation_code);
        d.step(1);

        /* 0 Spare    E    Number of parameters */
        auto num_param = d.uint8() & 0x3fu;
        d.add_item(&hf_qos_flow_ebit);
        d.add_item(&hf_sm_parameters_number);
        d.step(1);

        auto j = 1;
        while (num_param > 0) {
            const auto consumed = dissect_qos_parameters(d, j, ctx);
            d.step(consumed);
            ++j;
            --num_param;
        }
    }
    return d.offset - uc.offset;
}
