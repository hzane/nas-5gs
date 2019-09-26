#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.20 Configuration update complete */
int dissect_configuration_update_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "configuration-update-complete", d);
    // UE to network
    up_link(d.pinfo);

    /* No Data */

    return 0;
}
