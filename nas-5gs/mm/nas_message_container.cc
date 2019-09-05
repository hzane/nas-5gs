#include "../dissect_mm_msg.hh"

/* 9.11.3.33    NAS message container */
int mm::dissect_nas_msg_cont(dissector d, context* ctx) {
    /* The purpose of the NAS message container IE is to
     * encapsulate a plain 5GS NAS message. */
    /* a NAS message without NAS security heade */

    const use_context uc(ctx, "nas-msg-container", d, 0);

    dissect_nas5g(d, ctx);
    return uc.length;
}
