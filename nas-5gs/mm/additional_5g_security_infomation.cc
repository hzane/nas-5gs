#include "../dissect_mm_msg.hh"


int mm::dissect_selected_eps_sec_algo(dissector d, context* ctx) {
    diag("no dissect %s\n", ctx->path().c_str());
    return d.length;
}

using namespace nas;

// * 9.11.3.12    Additional 5G security information
int mm::dissect_a_sec_info(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_mm_rinmr,
        &hf_mm_hdp,
        nullptr,
    };

    d.add_bits(flags);

    return 1;
}
