#include "../common/dissector.hh"
#include "../common/use_context.hh"

// DRX parameters 9.11.3.2A
int dissect_drx_parameter(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "DRX parameters", -1);

    return 1;
}
