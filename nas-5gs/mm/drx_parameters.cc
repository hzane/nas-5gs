#include "../dissect_mm_msg.hh"

/* 9.11.3.2A    5GS DRX parameters*/
static const value_string nas_5gs_mm_drx_vals[] = {
    {0x0, "DRX value not specified"},
    {0x1, "DRX cycle parameter T = 32"},
    {0x2, "DRX cycle parameter T = 64"},
    {0x3, "DRX cycle parameter T = 128"},
    {0x4, "DRX cycle parameter T = 256"},
    {0, nullptr},
};
const field_meta mm::hf_drx_param = {
    "DRX value",
    "nas_5gs.mm.drx_value",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_mm_drx_vals),
    nullptr,
    nullptr,
    0x0f,
};

// DRX parameters 9.11.3.2A
int mm::dissect_drx_param(dissector d, context* ctx) {
    use_context uc(ctx, "DRX parameters", d, 0);

    d.add_item(1, &hf_drx_param, enc::be);
    return 1;
}
