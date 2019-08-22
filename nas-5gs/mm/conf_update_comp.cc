#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*
 * 8.2.20 Configuration update complete
 */
int mm::conf_update_comp(dissector d, context* ctx) {
    /* No Data */
    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
