#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

// * 9.11.3.12    Additional 5G security information
int mm::dissect_additional_security_info(dissector d, context* ctx) {
    const use_context        uc(ctx, "additional-5g-security-information", d, -1);

    static const field_meta* flags[] = {
        &hf_retransmission_of_initial_nas_request,
        &hf_horizontal_derivation_parameter,
        nullptr,
    };

    d.add_bits(flags);

    return 1;
}

struct additional_security_information_t{
    uint8_t mm_rinr;
    uint8_t mm_hdp;
};
