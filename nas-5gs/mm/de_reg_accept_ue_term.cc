#include "../dissect_mm_msg.hh"

// no body
int dissect_de_reg_accept_ue_term(dissector d, context* ctx) {
    const use_context uc(ctx, "deregistration-accept-ue-terminated", d, -1);
    down_link(d.pinfo);

    return 0;
}
