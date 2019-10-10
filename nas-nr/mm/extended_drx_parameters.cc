#include "../common/core.hh"
#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.60	Extended DRX parameters
// See subclause 10.5.5.32 in 3GPP TS 24.008 [12].
result_t die_extended_drx_parameters(dissector d, context*ctx, extended_drx_parameters_t*ret){
    ret->edrx = d.uint8(false) & 0x0fu;
    ret->paging_time_window = mask_u8(d.uint8(true), 0xf0u);
    return {1};
}