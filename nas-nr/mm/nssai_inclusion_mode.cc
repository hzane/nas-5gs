#include "../dissect_mm_msg.hh"

using namespace nas;
// 9.11.3.37A NSSAI inclusion mode page.381
// a type 1 information element
int mm::dissect_nssai_inclusion_mode(dissector d, context* ctx) {
    const use_context        uc(ctx, "nssai-inclusion-mode", d, -1);

    static const field_meta* flags[] = {
        // &hf_spare_b3,
        // &hf_spare_b2,
        &hf_nssai_inc_mode,
        nullptr,
    };
    d.add_bits(flags);
    
    return 1;
}

/* 9.11.3.37A   NSSAI inclusion mode */
static const value_string nas_5gs_mm_nssai_inc_mode_vals[] = {
    {0x00, "A"},
    {0x01, "B"},
    {0x02, "C"},
    {0x03, "D"},
    {0, nullptr},
};
const field_meta mm::hf_nssai_inc_mode = {
    "NSSAI inclusion mode",
    "nas_5gs.mm.nssai_inc_mode",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_nssai_inc_mode_vals,
    nullptr,
    nullptr,
    0x03,
};
