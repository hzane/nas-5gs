#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;

// * 9.11.3.12    Additional 5G security information
int mm::dissect_additional_security_info(dissector d, context* ctx) {
    const use_context        uc(ctx, "additional-5g-security-information", d, -1);

    d.add_item(&hf_retransmission_of_initial_nas_request);
    d.add_item(&hf_horizontal_derivation_parameter);
    d.step(1);

    return 1;
}

