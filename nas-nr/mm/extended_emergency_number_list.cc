#include "../common/dissector.hh"
#include "../common/use_context.hh"

// Extended emergency number list  9.11.3.26
int dissect_extended_emergency_number_list(dissector d, context* ctx) {
    // See subclause 9.9.3.37A in 3GPP TS 24.301 [15].
    const use_context uc(ctx, "extended-emergency-number-list", d, 0);

    return uc.length;
}
