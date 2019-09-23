#include "../common/dissect_mm_msg.hh"

/* 8.2.20 Configuration update complete */
int mm::dissect_configuration_update_complete(dissector d, context* ctx) {
    const use_context uc(ctx, "configuration-update-complete", d);
    // UE to network
    up_link(d.pinfo);

    /* No Data */

    return 0;
}

struct configuration_update_complete_t{

};
