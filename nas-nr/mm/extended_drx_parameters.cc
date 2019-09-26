#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.3.60	Extended DRX parameters
// See subclause 10.5.5.32 in 3GPP TS 24.008 [12].
int dissect_extended_drx_parameters(dissector d, context* ctx) {
    const use_context uc(ctx, "extended-drx-parameters", d, -1);

    return 1;
}
