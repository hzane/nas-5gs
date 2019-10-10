#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*  9.11.4.3 Always-on PDU session indication */

result_t die_always_on_pdu_session_indication(dissector                          d,
                                              context*                           ctx,
                                              always_on_pdu_session_indication_t* ret) {
    ret->apsi = d.uint8(true) & 0x01u;
    return {1};
}