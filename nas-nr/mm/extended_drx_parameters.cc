#include "../common/dissect_mm_msg.hh"

// 9.11.3.60	Extended DRX parameters
// See subclause 10.5.5.32 in 3GPP TS 24.008 [12].

/* [13] 10.5.5.32 Extended DRX parameters */
static const v_string paging_time_window_values[] = {
    {0x0, "Iu: 0 s / WB-S1: 1.28 s / NB-S1: 2.56 s"},
    {0x1, "Iu: 1 s / WB-S1: 2.56 s / NB-S1: 5.12 s"},
    {0x2, "Iu: 2 s / WB-S1: 3.84 s / NB-S1: 7.68 s"},
    {0x3, "Iu: 3 s / WB-S1: 5.12 s / NB-S1: 10.24 s"},
    {0x4, "Iu: 4 s / WB-S1: 6.4 s / NB-S1: 12.8 s"},
    {0x5, "Iu: 5 s / WB-S1: 7.68 s / NB-S1: 15.36 s"},
    {0x6, "Iu: 6 s / WB-S1: 8.96 s / NB-S1: 17.92 s"},
    {0x7, "Iu: 7 s / WB-S1: 10.24 s / NB-S1: 20.48 s"},
    {0x8, "Iu: 8 s / WB-S1: 11.52 s / NB-S1: 23.04 s"},
    {0x9, "Iu: 9 s / WB-S1: 12.8 s / NB-S1: 25.6 s"},
    {0xa, "Iu: 10 s / WB-S1: 14.08 s / NB-S1: 28.16 s"},
    {0xb, "Iu: 12 s / WB-S1: 15.36 s / NB-S1: 30.72 s"},
    {0xc, "Iu: 14 s / WB-S1: 16.64 s / NB-S1: 33.28 s"},
    {0xd, "Iu: 16 s / WB-S1: 17.92 s / NB-S1: 35.84 s"},
    {0xe, "Iu: 18 s / WB-S1: 19.2 s / NB-S1: 38.4 s"},
    {0xf, "Iu: 20 s / WB-S1: 20.48 s / NB-S1: 40.96 s"},
    {0, nullptr},
    };

static const v_string edrx_values[] = {
    {0x0, "GERAN: 1.88 s / UTRAN: 10.24 s / E-UTRAN: 5.12 s"},
    {0x1, "GERAN: 3.76 s / UTRAN: 20.48 s / E-UTRAN: 10.24 s"},
    {0x2, "GERAN: 7.53 s / UTRAN: 40.96 s / E-UTRAN: 20.48 s"},
    {0x3, "GERAN: 12.24 s / UTRAN: 81.92 s / E-UTRAN: 40.96 s"},
    {0x4, "GERAN: 24.48 s / UTRAN: 163.84 s / E-UTRAN: 61.44 s"},
    {0x5, "GERAN: 48.96 s / UTRAN: 327.68 s / E-UTRAN: 81.92 s"},
    {0x6, "GERAN: 97.92 s / UTRAN: 655.36 s / E-UTRAN: 102.4 s"},
    {0x7, "GERAN: 195.84 s / UTRAN: 1310.72 s / E-UTRAN: 122.88 s"},
    {0x8, "GERAN: 391.68 s / UTRAN: 1966.08 s / E-UTRAN: 143.36 s"},
    {0x9, "GERAN: 783.36 s / UTRAN: 2621.44 s / E-UTRAN: 163.84 s"},
    {0xa, "GERAN: 1566.72 s / UTRAN: 10.24 s / E-UTRAN: 327.68 s"},
    {0xb, "GERAN: 3133.44 s / UTRAN: 10.24 s / E-UTRAN: 655.36 s"},
    {0xc, "GERAN: 1.88 s / UTRAN: 10.24 s / E-UTRAN: 1310.72 s"},
    {0xd, "GERAN: 1.88 s / UTRAN: 10.24 s / E-UTRAN: 2621.44 s"},
    {0xe, "GERAN: 1.88 s / UTRAN: 10.24 s / E-UTRAN: 5242.88 s"},
    {0xf, "GERAN: 1.88 s / UTRAN: 10.24 s / E-UTRAN: 10485.76 s"},
    {0, nullptr},
    };

const field_meta hf_paging_time_window = {
    "Paging Time Window",
    "gsm.paging_time_window",
    ft::ft_uint8,
    fd::base_hex,
    paging_time_window_values,
    nullptr,
    nullptr,
    0xf0u,
};
const field_meta hf_edrx_value = {
    "eDRX value",
    "gsm.gm.edrx",
    ft::ft_uint8,
    fd::base_hex,
    edrx_values,
    nullptr,
    nullptr,
    0x0fu,
};

int mm::dissect_extended_drx_parameters(dissector d, context* ctx) {
    const use_context uc(ctx, "extended-drx-parameters", d, -1);

    d.add_item(1, &hf_paging_time_window, enc::be);
    d.add_item(1, &hf_edrx_value, enc::be);
    d.step(1);

    return 1;
}