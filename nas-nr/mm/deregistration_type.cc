#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* De-registration type    De-registration type     9.11.3.20   M   V   1 */
int dissect_deregistration_type(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-type", d, -1);

    return 1;
}
