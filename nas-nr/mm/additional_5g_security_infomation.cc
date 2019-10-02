#include "../common/dissector.hh"
#include "../common/use_context.hh"

// * 9.11.3.12    Additional 5G security information
int dissect_additional_security_info(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "additional-5g-security-information", -1);

    return 1;
}
