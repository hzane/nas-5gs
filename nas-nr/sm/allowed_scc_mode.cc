#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../common/dissect_sm_msg.hh"

/* 9.11.4.5    Allowed SSC mode */
int dissect_allowed_ssc_mode(dissector d, context* ctx) {
    const use_context        uc(ctx, "allowed-scc-mode", d, -1);


    return 1;
}
