#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* *   9.11.3.46    Rejected NSSAI page.389 */
int dissect_rejected_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "rejected-nssai", d, 0);
    return uc.length;
}
