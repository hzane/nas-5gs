#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.6    5GS registration result
int dissect_registration_result(dissector d, context* ctx) {
    use_context uc(ctx, "5gs-registration-result", d, -1);

    /* 0 Spare 0 Spare 0 Spare 0 Spare SMS allowed 5GS registration result value */

    return 1;
}
