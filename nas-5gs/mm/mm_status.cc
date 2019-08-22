#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"
/*
 * 8.2.29 5GMM status
 */
int mm::mm_status(dissector d, context* ctx) {
    /* Direction: both*/
    /* 5GMM cause    5GMM cause 9.11.3.2    M    V    1 */
    // ELEM_MAND_V(NAS_5GS_PDU_TYPE_MM,
    //             DE_NAS_5GS_MM_5GMM_CAUSE,
    //             NULL,
    //             ei_nas_5gs_missing_mandatory_elemen);

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
