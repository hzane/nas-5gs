#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* * 9.11.3.3 5GS identity type */
int dissect_identity_type(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "5gs-identity-type", -1);


    return 1;
}
