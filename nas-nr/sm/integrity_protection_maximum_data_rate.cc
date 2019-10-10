#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

//  * 9.11.4.7 Integrity protection maximum data rate
result_t die_integrity_protection_maximum_data_rate(
    dissector                                 d,
    context*                                  ctx,
    integrity_protection_maximum_data_rate_t* ret) {
    const use_context uc(&d, ctx, "integrity-protection-maximum-data-rate", 0);
    /* Maximum data rate per UE for user-plane integrity protection for uplink */
    ret->uplink = d.uint8(true);
    /* Maximum data rate per UE for user-plane integrity protection for downlink */
    ret->downlink = d.uint8(true);
    return {2};
}
