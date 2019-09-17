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
struct nssai_inclusion_mode_t {
    uint8_t inclusion_mode;
};

/* 9.11.3.37A   NSSAI inclusion mode */
const value_string inclusion_mode_values[] = {
    {0x00, "A"},
    {0x01, "B"},
    {0x02, "C"},
    {0x03, "D"},
    {0, nullptr},
};
const field_meta mm::hf_nssai_inc_mode = {
    "NSSAI inclusion mode",
    "nas.nr.mm.nssai_inc_mode",
    ft::ft_uint8,
    fd::base_dec,
    inclusion_mode_values,
    nullptr,
    nullptr,
    0x03,
};
