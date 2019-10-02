#include "../common/dissector.hh"
#include "../common/use_context.hh"

//  * 9.11.4.7 Integrity protection maximum data rate
int dissect_integrity_protection_max_data_rate(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "integrity-protection-max-data-rate", -1);

    /* Maximum data rate per UE for user-plane integrity protection for uplink */

    /* Maximum data rate per UE for user-plane integrity protection for downlink */

    return 2;
}
