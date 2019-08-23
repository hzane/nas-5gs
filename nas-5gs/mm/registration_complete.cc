#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"


/*
 * 8.2.8 Registration complete
 */
int mm::registration_complete(dissector d, context* ctx) {
    use_context uc(ctx, "registration-complete");

    /* 73    SOR transparent container    SOR transparent container 9.11.3.51    O TLV-E
     * 20-2048 */
    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
