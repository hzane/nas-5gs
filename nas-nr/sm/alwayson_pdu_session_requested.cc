#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.4.4 Always-on PDU session requested
result_t die_always_on_pdu_session_requested(dissector                          d,
                                             context*                           ctx,
                                             always_on_pdu_session_requested_t* ret) {
    ret->apsr = d.uint8(true) & 0x01u;
    return {1};
}
