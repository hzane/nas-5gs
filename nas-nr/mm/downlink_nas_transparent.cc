#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.11 DL NAS transport */
int dissect_dl_nas_transparent(dissector d, context* ctx) {
    const use_context uc(ctx, "dl-nas-transport", d, 0);
    // network to UE
    down_link(d.pinfo);

    return uc.length;
}
