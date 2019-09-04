#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/* 8.2.20 Configuration update complete */
int mm::conf_update_comp(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "configuration-update-complete", d);

    /* No Data */
    d.extraneous_data_check(0);
    return len;
}
