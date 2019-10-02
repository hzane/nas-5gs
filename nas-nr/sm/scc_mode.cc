#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.4.16    SSC mode */
int dissect_ssc_mode(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ssc-mode", -1);

    return 1;
}
