#include "../common/dissect_sm_msg.hh"

/*  9.11.4.16    SSC mode */
int sm::dissect_ssc_mode(dissector d, context* ctx) {
    const use_context uc(ctx, "ssc-mode", d, -1);

    (void) d.add_item(1, &hf_ssc_mode, enc::be);

    return 1;
}

extern const element_meta sm::ssc_mode = {
    0xa0,
    "SSC mode",
    sm::dissect_ssc_mode,
    nullptr,
};

/*  9.11.4.16    SSC mode */
const v_string ssc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0x4, "SSC mode 1"},
    {0x5, "SSC mode 2"},
    {0x6, "SSC mode 3"},
    {0, nullptr},
};


const field_meta sm::hf_ssc_mode_3 = {
    "SSC mode 3",
    "nas.nr.sm.all.ssc.mode.3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas::tfs_allowed_not_allowed,
    nullptr,
    0x04,
};
const field_meta sm::hf_ssc_mode_2 = {
    "SSC mode 2",
    "nas.nr.sm.all.ssc.mode.2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas::tfs_allowed_not_allowed,
    nullptr,
    0x02,
};
const field_meta sm::hf_ssc_mode_1 = {
    "SSC mode 1",
    "nas.nr.sm.all.ssc.mode.1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &sm::tfs_allowed_not_allowed,
    nullptr,
    0x01,
};

/*  9.11.4.16    SSC mode */
extern const v_string sm::ssc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0, nullptr},
};

const field_meta sm::hf_ssc_mode = {
    "SSC mode",
    "nas.nr.sm.ssc.mode",
    ft::ft_uint8,
    fd::base_dec,
    sm::ssc_mode_values,
    nullptr,
    nullptr,
    0x0f,
};
