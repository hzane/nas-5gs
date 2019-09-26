#include "../base/ber.hh"
#include "../common/dissect_mm_msg.hh"

/* 8.2.10    UL NAS transport */
int dissect_ul_nas_transport(dissector d, context* ctx) {
    const use_context uc(ctx, "ul-nas-transport", d, 1);

    /* Direction: UE to network */
    up_link(d.pinfo);



    return uc.length;
}
