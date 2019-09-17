#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

/* *   9.11.3.34    NAS security algorithms */
int mm::dissect_security_algo(dissector d, context* ctx) {
    const use_context uc(ctx, "sec-algo", d, -1);

    static const field_meta* flags[] = {
        &hf_sec_algo_enc,
        &hf_sec_algo_ip,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

struct security_algorithm_t {
    uint8_t ciphering_algo;
    uint8_t integrity_algo;
};

/* *   9.11.3.34    NAS security algorithms */
extern const val_string mm::integrity_protection_algo_type_values[] = {
    {0x0, "5G-IA0 (null integrity protection algorithm)"},
    {0x1, "128-5G-IA1"},
    {0x2, "128-5G-IA2"},
    {0x3, "128-5G-IA3"},
    {0x4, "5G-IA4"},
    {0x5, "5G-IA5"},
    {0x6, "5G-IA6"},
    {0x7, "5G-IA7"},
    {0, nullptr},
};

const field_meta mm::hf_sec_algo_ip = {
    "Type of integrity protection algorithm",
    "nas.nr.mm.nas_sec_algo_ip",
    ft::ft_uint8,
    fd::base_dec,
    integrity_protection_algo_type_values,
    nullptr,
    nullptr,
    0x0f,
};
