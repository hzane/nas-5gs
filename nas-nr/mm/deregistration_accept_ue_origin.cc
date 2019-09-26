#include "../common/dissector.hh"
#include "../common/use_context.hh"

// no body
int dissect_deregistration_accept_ue_origin(dissector d, context* ctx) {
    const use_context uc(ctx, "deregistration-accept-ue-origin", d, -1);
    // network to UE
    down_link(d.pinfo);

    return 0;
}
