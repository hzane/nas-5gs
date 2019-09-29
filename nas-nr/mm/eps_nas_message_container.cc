#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* 9.11.3.24    EPS NAS message container */
int mm::dissect_eps_nas_msg_container(dissector d, context* ctx) {
    const use_context uc(ctx, "eps-nas-message-container", d, 0);

    diag("no eps dissector\n");
    // An EPS NAS message as specified in 3GPP TS 24.301
    d.step(d.length);

    return d.length;
}
