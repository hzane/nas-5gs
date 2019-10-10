#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.4.14    Session-AMBR
result_t die_session_tmbr(dissector d, context* ctx, session_tmbr_t*ret){
    const use_context uc(&d, ctx, "session-tmbr", 0);
    ret->downlink_unit = d.uint8(true);
    ret->downlink      = d.uint16(true);
    ret->uplink_unit   = d.uint8(true);
    ret->uplink        = d.uint16(true);

    return {6};
}

result_t die_session_ambr(dissector d, context* ctx, session_ambr_t*ret){
    const use_context uc(&d, ctx, "session-ambr", 0);

    ret->downlink_unit = d.uint8(true);
    ret->downlink      = d.uint16(true);
    ret->uplink_unit   = d.uint8(true);
    ret->uplink        = d.uint16(true);
    return {6};
}