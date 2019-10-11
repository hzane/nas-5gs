#include "../common/ber.hh"
#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.13    Allowed PDU session status */
result_t dissect_allowed_pdu_session_status(dissector                    d,
                                            context*                     ctx,
                                            allowed_pdu_session_status_t ret) {
    return de_fixed(d, ctx, ret);
}
