#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"
/*
 * 8.2.29 5GMM status
 */
int mm::mm_status(dissector d, context* ctx) {
    auto        len = d.length;
    use_context uc(ctx, "5gmm-status");

    /* Direction: both*/
    d.pinfo->dir = pi_dir::both;

    /* 5GMM cause    5GMM cause 9.11.3.2    M    V    1 */
    // ELEM_MAND_V(DE_NAS_5GS_MM_5GMM_CAUSE,ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}
