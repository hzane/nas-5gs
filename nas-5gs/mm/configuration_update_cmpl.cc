#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 8.2.20 Configuration update complete */
int mm::dissect_config_update_cmpl(dissector d, context* ctx) {    
    const use_context uc(ctx, "configuration-update-complete", d);
    // UE to network
    up_link(d.pinfo);

    /* No Data */
    
    return 0;
}
