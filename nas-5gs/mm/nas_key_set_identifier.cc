#include "../dissect_mm_msg.hh"


// NAS key set identifier 9.11.3.32
const element_meta mm::key_set_id = {
    0xff,
    "NAS key set identifier - ngKSI",
    dissect_nas_ksi,
    nullptr,
};

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

