#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.3.13 PDU session release reject */
result_t de_pdu_session_release_reject(dissector                     d,
                                       context*                      ctx,
                                       pdu_session_release_reject_t* ret) {
    const use_context uc(&d, ctx, "pdu-session-release-reject", 0);
    /* Direction: network to UE */
    down_link(d.pinfo);

    de_nsm_header(d, ctx, &ret->header);

    de_uint8(d, ctx, &ret->cause).step(d);
    de_tle_octet(d, ctx, 0x7b, &ret->extended_pco).step(d);
    return {uc.consumed()};
}
