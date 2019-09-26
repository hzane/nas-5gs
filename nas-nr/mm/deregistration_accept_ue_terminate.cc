#include "../common/dissector.hh"
#include "../common/use_context.hh"

// no body
int dissect_deregistration_accept_ue_terminate(dissector d, context* ctx) {
    const use_context uc(ctx, "deregistration-accept-ue-terminated", d, -1);
    // UE to network
    up_link(d.pinfo);

    return 0;
}
