#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.2.20 Configuration update complete
 */
int mm::conf_update_comp(dissector d, context* ctx) {
    use_context uc(ctx, "configuration-update-complete");

    /* No Data */
    d.extraneous_data_check(0);
    return d.tvb->reported_length;
}
