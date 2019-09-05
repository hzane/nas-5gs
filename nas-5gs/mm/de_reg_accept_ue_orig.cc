#include "../dissect_mm_msg.hh"

// no body
int dissect_de_reg_accept_ue_orig(dissector d, context* ctx) {
    const use_context uc(ctx, "deregistration-accept-ue-origin", d, -1);
    up_link(d.pinfo);

    return 0;
}
