#include "../dissect_mm_msg.hh"


// 9.11.3.32	NAS key set identifier
int mm::dissect_nas_ksi(dissector d, context* ctx) {
    use_context uc(ctx, "NAS key set identifier", d, -1);

    static const field_meta* flags[] = {
        &hf_tsc,
        hf_nas_eps_nas_ksi, //& hf_nas_key_set_id,
        nullptr,
    };

    /* NAS key set identifier IEI   TSC     NAS key set identifier */
    d.add_bits(flags);
    d.step(1);

    return 1;
}


/* NAS key set identifier (octet 1) Bits 3  2   1 */
extern const val_string mm::nas_eps_emm_nas_ksi_values[] = {
    {0, ""},
    {1, ""},
    {2, ""},
    {3, ""},
    {4, ""},
    {5, ""},
    {6, ""},
    {7, "No key is available"},
    {0, nullptr},
};

const field_meta mm::hf_nas_key_set_id = {
    "NAS key set identifier",
    "nas_5gs.mm.nas_key_set_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_eps_emm_nas_ksi_values,
    nullptr,
    nullptr,
    0x07,
};

// only spare half octet
const field_meta mm::hf_ngksi_nas_ksi = {
    "NAS key set identifier - ngKSI",
    "nas_5gs.mm.ngksi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xF0,
};

// NAS key set identifier 9.11.3.32
extern const element_meta mm::nas_ksi = {
    0xff,
    "NAS key set identifier - ngKSI",
    dissect_nas_ksi,
    nullptr,
};

