#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../common/dissects.hh"

/* 9.11.4.5    Allowed SSC mode */
int dissect_allowed_ssc_mode(dissector d, context* ctx) {
    const use_context        uc(&d, ctx, "allowed-scc-mode", -1);


    return 1;
}
