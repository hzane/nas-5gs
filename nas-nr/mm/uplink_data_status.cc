#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
result_t die_uplink_data_status(dissector d, context* ctx, uplink_data_status_t* ret) {
    ret->psi_a = d.uint8(true);
    ret->psi_b = d.uint8(true);

    return {2};
}