#include "../dissect_mm_msg.hh"

// no body
int mm::dissect_deregistration_accept_ue_orig(dissector d, context* ctx) {
    const use_context uc(ctx, "deregistration-accept-ue-origin", d, -1);
    // network to UE
    down_link(d.pinfo);

    return 0;
}
