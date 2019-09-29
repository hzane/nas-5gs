#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

// no body
int mm::dissect_deregistration_accept_ue_terminate(dissector d, context* ctx) {
    const use_context uc(ctx, "deregistration-accept-ue-terminated", d, -1);
    // UE to network
    up_link(d.packet);

    return 0;
}
