#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

using namespace sm;
using namespace nas;

/* 9.11.4.8 Mapped EPS bearer contexts */
int dissect_eps_parameters(dissector d, int i, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);

    auto     subtree = d.add_item(-1, formats("EPS parameter %u", i));
    use_tree ut(d, subtree);

    /* EPS parameter identifier */
    const auto param_id = static_cast< uint32_t >(d.uint8());
    (void) d.add_item(1, &hf_eps_parameter_id);
    d.step(1);

    /*length of the EPS parameter contents field */
    const auto length = static_cast< int >(d.uint8());
    // (void) d.add_item(1, &hf_sm_length);
    d.step(1);

    subtree->set_length(length + 2);
    /*length of the EPS parameter contents field */
    switch (param_id) {
    case 1: /* 01H (Mapped EPS QoS parameters) */
    case 2: /* 02H (Mapped extended EPS QoS parameters) */
    case 3: /* 03H (Traffic flow template)*/
    case 4: /* 04H (APN-AMBR) */
    case 5: /* 05H (extended APN-AMBR). */
    default:
        (void) d.add_item(length, &hf_eps_parameter_contents);
        d.step(length);
    }
    return d.offset - uc.offset;
}


// Mapped EPS  bearer contexts     9.11.4.8
int sm::dissect_mapped_eps_bearer_contexts(dissector d, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);

    auto n = 1;
    /* The IE contains a number of Mapped EPS bearer context */
    while (d.length > 0) {
        /* Figure 9.11.4.5.2: Mapped EPS bearer context */
        auto     subtree = d.add_item(-1, formats("Mapped EPS bearer context %u", n));
        use_tree ut(d, subtree);

        /* EPS bearer identity */
        (void) d.add_item(1, &hf_eps_bearer_content_id);
        d.step(1);

        /* Length of Mapped EPS bearer context*/
        const auto length = static_cast< int >(d.uint16());
        // (void) d.add_item(2, &hf_sm_length);
        d.step(2);

        subtree->set_length(length + 3);
        /*     8   7      6    5   4  3  2  1          */
        /* operation code | spare |  E | number of EPS params     */

        auto       nep      = d.tvb->uint8(d.offset);
        const auto opt_code = (nep & 0xc0u) >> 6u;
        nep                 = nep & 0x0fu;

        /* operation code = 3 Modify existing EPS bearer */
        if (opt_code == 3) {
            d.add_item(&hf_sm_bearer_content_operation_code);
            d.add_item(&hf_bearer_ebit);
            d.add_item(&hf_eps_parameters_numbers);
        } else {
            d.add_item(&hf_sm_bearer_content_operation_code);
            d.add_item(&hf_eps_ebit_modify);
            d.add_item(&hf_eps_parameters_numbers);
        }
        d.step(1);

        /* EPS parameters list */
        auto i = 1;
        while (nep > 0) {
            auto consumed = dissect_eps_parameters(d, i, ctx);
            d.step(consumed);
            --nep;
            ++i;
        }
        ++n;
    }
    return uc.length;
}


// Mapped EPS  bearer contexts     9.11.4.5
const element_meta sm::mapped_eps_bearer_context = {
    0x75,
    "Mapped EPS bearer contexts",
    dissect_mapped_eps_bearer_contexts,
};


/* 9.11.4.8 Mapped EPS bearer contexts */
extern const value_string sm::operation_code_values[] = {
    {0x0, "Reserved"},
    {0x01, "Create new EPS bearer"},
    {0x02, "Delete existing EPS bearer"},
    {0x03, "Modify existing EPS bearer"},
    {0, nullptr},
};

extern const value_string sm::deb_bit_values[] = {
    {0x0, "the EPS bearer is not the default EPS bearer."},
    {0x01, "the EPS bearer is the default EPS bearer"},
    {0, nullptr},
};

extern const value_string sm::e_bit_values[] = {
    {0x0, "parameters list is not included"},
    {0x01, "parameters list is included"},
    {0, nullptr},
};

extern const value_string sm::e_bit_modify_values[] = {
    {0x0, "previously provided parameters list extension"},
    {0x01, "previously provided parameters list replacement"},
    {0, nullptr},
};

extern const value_string sm::eps_parameter_identity_values[] = {
    {0x01, "Mapped EPS QoS parameters"},
    {0x02, "Mapped extended EPS QoS parameters"},
    {0x03, "Traffic flow template"},
    {0x04, "APN-AMBR"},
    {0x05, "extended APN-AMBR"},
    {0, nullptr},
};

const tag_field sm::hf_sm_bearer_content_operation_code = {
    "Operation code",
    0xc0,
    (const v_string[]){
        {0x0, "Reserved"},
        {0x01, "Create new EPS bearer"},
        {0x02, "Delete existing EPS bearer"},
        {0x03, "Modify existing EPS bearer"},
        {0, nullptr},
    },
};
const tag_field sm::hf_eps_bearer_deb = {
    "DEB bit",
    0x20,
    deb_bit_values,
};
const bool_field sm::hf_bearer_ebit = {
    "E bit",
    0x10,
    "parameters list is included",
    "parameters list is not included",
};
const uint8_field sm::hf_eps_parameters_numbers = {
    "Number of EPS parameters",
    0x0f,
};
const bool_field sm::hf_eps_ebit_modify = {
    "E bit",
    0x10,
    hf_bearer_ebit.values
};

const uint8_field sm::hf_eps_bearer_content_id = {
    "EPS bearer identity",
    0xf0,
};
const tag_field sm::hf_eps_parameter_id = {
    "EPS parameter identity",
    0x0,
    eps_parameter_identity_values,
};
const octet_field sm::hf_eps_parameter_contents = {
    "EPS parameter contents",
};
