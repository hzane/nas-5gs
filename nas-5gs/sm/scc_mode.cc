#include "../dissect_sm_msg.hh"

/*  9.11.4.16    SSC mode */
int sm::dissect_ssc_mode(dissector d, context* ctx) {
    d.add_item(1, &hf_sm_sc_mode, enc::be);
    return 1;
}

extern const element_meta sm::ssc_mode = {
    0xa0,
    "SSC mode",
    dissect_ssc_mode,
    nullptr,
};

/*  9.11.4.16    SSC mode */
const val_string nas_5gs_sc_mode_values[] = {
    {0x1, "SSC mode 1"},
    {0x2, "SSC mode 2"},
    {0x3, "SSC mode 3"},
    {0, nullptr},
};

// Selected SSC mode    SSC mode 9.11.4.16
extern const field_meta sm::hfm_sel_sc_mode = {
    "Selected SSC mode",
    "nas_5gs.sm.sel_sc_mode",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_sc_mode_values,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta* sm::hf_sel_sc_mode = &sm::hfm_sel_sc_mode;
