#include "../dissect_sm_msg.hh"

using namespace sm;
using namespace nas;

/* 9.11.4.8 Mapped EPS bearer contexts */
int dissect_eps_param(dissector d, int i, context* ctx) {
    auto     start   = d.offset;
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

    subtree->set_length(length + 2);
    /*length of the EPS parameter contents field */
    switch (param_id) {
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
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);
    
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
    while (d.length > 0) {
        /* Figure 9.11.4.5.2: Mapped EPS bearer context */
        auto     subtree = d.add_item(-1, "Mapped EPS bearer context %u", n);
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

        auto nep      = d.tvb->uint8(d.offset);
        auto opt_code = (nep & 0xc0u) >> 6u;
        nep           = nep & 0x0f;

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
            auto consumed = dissect_eps_param(d, i, ctx);
            d.step(consumed);
            --nep;
            ++i;
        }
        ++n;
    }
    return uc.length;
}


// Mapped EPS  bearer contexts     9.11.4.5
const element_meta sm::mapped_eps_b_cont = {
    0x75,
    "Mapped EPS bearer contexts",
    dissect_mapped_eps_b_cont,
    nullptr,
};


/* 9.11.4.8 Mapped EPS bearer contexts */
extern const value_string sm::sm_mapd_eps_b_cont_opt_code_values[] = {
    {0x0, "Reserved"},
    {0x01, "Create new EPS bearer"},
    {0x02, "Delete existing EPS bearer"},
    {0x03, "Modify existing EPS bearer"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_deb_values[] = {
    {0x0, "the EPS bearer is not the default EPS bearer."},
    {0x01, "the EPS bearer is the default EPS bearer"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_e_values[] = {
    {0x0, "parameters list is not included"},
    {0x01, "parameters list is included"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_E_Modify_values[] = {
    {0x0, "previously provided parameters list extension"},
    {0x01, "previously provided parameters list replacement"},
    {0, nullptr},
};

extern const value_string sm::sm_mapd_eps_b_cont_param_id_values[] = {
    {0x01, "Mapped EPS QoS parameters"},
    {0x02, "Mapped extended EPS QoS parameters"},
    {0x03, "Traffic flow template"},
    {0x04, "APN-AMBR"},
    {0x05, "extended APN-AMBR"},
    {0, nullptr},
};

const field_meta sm::hf_sm_mapd_eps_b_cont_opt_code = {
    "Operation code",
    "nas_5gs.sm.mapd_eps_b_cont_opt_code",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_opt_code_values,
    nullptr,
    nullptr,
    0xc0,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_deb = {
    "DEB bit",
    "nas_5gs.sm.mapd_eps_b_cont_DEB",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_deb_values,
    nullptr,
    nullptr,
    0x20,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_e = {
    "E bit",
    "nas_5gs.sm.mapd_eps_b_cont_E",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_e_values,
    nullptr,
    nullptr,
    0x10,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_num_eps_parms = {
    "Number of EPS parameters",
    "nas_5gs.sm.mapd_eps_b_cont_num_eps_parms",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0f,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_e_mod = {
    "E bit",
    "nas_5gs.sm.mapd_eps_b_cont_E_mod",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_E_Modify_values,
    nullptr,
    nullptr,
    0x10,
};

const field_meta sm::hf_sm_mapd_eps_b_cont_id = {
    "EPS bearer identity",
    "nas_5gs.sm.mapd_eps_b_cont_id",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_num_eps_param_id = {
    "EPS parameter identity",
    "nas_5gs.sm.mapd_eps_b_cont_param_id",
    ft::ft_uint8,
    fd::base_dec,
    sm_mapd_eps_b_cont_param_id_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta sm::hf_sm_mapd_eps_b_cont_eps_param_cont = {
    "EPS parameter contents",
    "nas_5gs.sm.mapd_eps_b_cont_eps_param_cont",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
