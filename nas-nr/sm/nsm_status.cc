#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.3.16 5GSM status */
result_t de_nsm_status(dissector d, context* ctx, nsm_status_t* ret) {
    const use_context uc(&d, ctx, "nsm-status", 0);
    de_nsm_header(d, ctx, &ret->header);

    de_uint8(d, ctx, &ret->nsm_cause).step(d);
    return {uc.consumed()};
}
