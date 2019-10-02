#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.24    EPS NAS message container */
int dissect_eps_nas_msg_container(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "eps-nas-message-container", 0);

    return d.length;
}
