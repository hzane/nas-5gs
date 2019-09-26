#include "../common/dissector.hh"
#include "../common/use_context.hh"

// Emergency number list  9.11.3.23
int dissect_emergency_number_list(dissector d, context* ctx) {
    const use_context uc(ctx, "emergency-number-list", d, 0);

    return 0;
}
