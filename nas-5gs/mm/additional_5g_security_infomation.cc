#include "../dissect_mm_msg.hh"


using namespace nas;

// * 9.11.3.12    Additional 5G security information
int mm::dissect_additional_security_info(dissector d, context* ctx) {
    const use_context        uc(ctx, "additional-5g-security-information", d, -1);

    static const field_meta* flags[] = {
        &hf_mm_rinmr,
        &hf_mm_hdp,
        nullptr,
    };

    d.add_bits(flags);

    return 1;
}
