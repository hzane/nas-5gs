#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.12 PDU session release request */
result_t de_pdu_session_release_request(dissector                      d,
                                        context*                       ctx,
                                        pdu_session_release_request_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-release-rquest", 0);
    /* Direction: UE to network */
    up_link(d.pinfo);

    de_nsm_header(d, ctx, &ret->header);

    de_t_uint8(d, ctx, 0x59, &ret->nsm_cause).step(d);
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);
    return {uc.consumed()};
}
