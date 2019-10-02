#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.10    UL NAS transport */
int dissect_ul_nas_transport(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ul-nas-transport", 1);

    /* Direction: UE to network */
    up_link(d.pinfo);



    return uc.length;
}
