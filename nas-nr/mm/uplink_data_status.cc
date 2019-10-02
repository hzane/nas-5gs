#include "../common/dissector.hh"
#include "../common/use_context.hh"


/*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
int dissect_uplink_data_status(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "uplink-data-status", -1);

    return 2;
}
