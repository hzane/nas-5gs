#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.8 Registration complete */
int dissect_registration_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-complete", d);

    up_link(d.pinfo);

    /* 73    SOR transparent container 9.11.3.51    O TLV-E 20-2048 */

    return uc.length;
}
