#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* * 9.11.3.3 5GS identity type */
int dissect_identity_type(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-identity-type", d, -1);

    (void) d.add_item(1, &hf_identity_type, enc::be);
    d.step(1);

    return 1;
}
