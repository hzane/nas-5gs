#include "../common/dissect_sm_msg.hh"

using namespace sm;
using namespace nas;

struct eps_parameters_t {
    uint8_t   identifier;
    payload_t content;
};
/* 9.11.4.8 Mapped EPS bearer contexts */
int dissect_eps_parameters(dissector d, int i, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);

    auto     subtree = d.add_item(-1, "EPS parameter %u", i);
    use_tree ut(d, subtree);

    /* EPS parameter identifier */
    const auto param_id = static_cast< uint32_t >(d.uint8());
    (void) d.add_item(1, &hf_eps_parameter_id, enc::be);
    d.step(1);

    /*length of the EPS parameter contents field */
    const auto length = static_cast< int >(d.uint8());
    // (void) d.add_item(1, &hf_sm_length, enc::be);
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
        (void) d.add_item(length, &hf_eps_parameter_contents, enc::be);
        d.step(length);
    }
    return d.offset - uc.offset;
}

struct eps_parameter_t {

};
struct bearer_context_t {
    uint8_t                        identity;
    std::vector< eps_parameter_t > parameters;
};
struct mapped_eps_bearer_contexts_t {
    uint8_t operation_code;
    uint8_t ebit;
    uint8_t parameters_number;
    std::vector< bearer_context_t > contexts;
};
// Mapped EPS  bearer contexts     9.11.4.8
int sm::dissect_mapped_eps_bearer_contexts(dissector d, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);

    static const field_meta* mapd_eps_b_cont_flags[] = {
        &hf_sm_bearer_content_operation_code,
        &hf_bearer_ebit,
        &hf_eps_parameters_numbers,
        nullptr,
    };

    static const field_meta* mapd_eps_b_cont_flags_modify[] = {
        &hf_sm_bearer_content_operation_code,
        &hf_eps_ebit_modify,
        &hf_eps_parameters_numbers,
        nullptr,
    };
    auto n = 1;
    /* The IE contains a number of Mapped EPS bearer context */
    while (d.length > 0) {
        /* Figure 9.11.4.5.2: Mapped EPS bearer context */
        auto     subtree = d.add_item(-1, "Mapped EPS bearer context %u", n);
        use_tree ut(d, subtree);

        /* EPS bearer identity */
        (void) d.add_item(1, &hf_eps_bearer_content_id, enc::be);
        d.step(1);

        /* Length of Mapped EPS bearer context*/
        const auto length = static_cast< int >(d.ntohs());
        // (void) d.add_item(2, &hf_sm_length, enc::be);
        d.step(2);

        subtree->set_length(length + 3);
        /*     8   7      6    5   4  3  2  1          */
        /* operation code | spare |  E | number of EPS params     */

        auto       nep      = d.tvb->uint8(d.offset);
        const auto opt_code = (nep & 0xc0u) >> 6u;
        nep                 = nep & 0x0fu;

        /* operation code = 3 Modify existing EPS bearer */
        if (opt_code == 3) {
            d.add_bits(mapd_eps_b_cont_flags_modify);
        } else {
            d.add_bits(mapd_eps_b_cont_flags);
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
    nullptr,
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

const field_meta sm::hf_sm_bearer_content_operation_code = {
    "Operation code",
    "nas.nr.sm.mapd_eps_b_cont_opt_code",
    ft::ft_uint8,
    fd::base_dec,
    operation_code_values,
    nullptr,
    nullptr,
    0xc0,
};
const field_meta sm::hf_eps_bearer_deb = {
    "DEB bit",
    "nas.nr.deb",
    ft::ft_uint8,
    fd::base_dec,
    deb_bit_values,
    nullptr,
    nullptr,
    0x20,
};
const field_meta sm::hf_bearer_ebit = {
    "E bit",
    "nas.nr.sm.e-bit",
    ft::ft_uint8,
    fd::base_dec,
    e_bit_values,
    nullptr,
    nullptr,
    0x10,
};
const field_meta sm::hf_eps_parameters_numbers = {
    "Number of EPS parameters",
    "nas.nr.eps.parameters",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};
const field_meta sm::hf_eps_ebit_modify = {
    "E bit",
    "nas.nr.sm.e-bit.modify",
    ft::ft_uint8,
    fd::base_dec,
    e_bit_modify_values,
    nullptr,
    nullptr,
    0x10,
};

const field_meta sm::hf_eps_bearer_content_id = {
    "EPS bearer identity",
    "nas.nr.sm.bearer.identity",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta sm::hf_eps_parameter_id = {
    "EPS parameter identity",
    "nas.nr.sm.eps.parameter",
    ft::ft_uint8,
    fd::base_dec,
    eps_parameter_identity_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_eps_parameter_contents = {
    "EPS parameter contents",
    "nas.nr.sm.eps.parameter",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
