#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.56
result_t die_ue_status(dissector d, context* ctx, ue_status_t* ret) {
    /* 0     0     0     0     0     0 Spare    S1  mode reg */
    ret->s1_mode_reg = d.uint8(false) & 0x01u;
    ret->n1_mode_reg = d.uint8(true) & 0x02u;
    return {1};
}