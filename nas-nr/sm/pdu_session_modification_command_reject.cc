#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.11	PDU session modification command reject */
result_t de_pdu_session_modification_command_reject(
    dissector                                  d,
    context*                                   ctx,
    pdu_session_modification_command_reject_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-modification-command-reject", 0);
    /* Direction: UE to network */
    up_link(d.pinfo);

    de_nsm_header(d, ctx, &ret->header);

    de_uint8(d, ctx, &ret->nsm_cause).step(d);
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);
    return {uc.consumed()};
}