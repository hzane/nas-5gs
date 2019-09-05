#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 8.2.20 Configuration update complete */
int mm::dissect_conf_update_comp(dissector d, context* ctx) {    
    const use_context uc(ctx, "configuration-update-complete", d);

    /* No Data */
    
    return 0;
}
