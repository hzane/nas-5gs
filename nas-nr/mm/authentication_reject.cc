#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.5 Authentication reject */
int dissect_authentication_reject(dissector d, context* ctx) {
    const use_context uc(ctx, "authentication-reject", d, 0);

    /* 78    EAP message  9.11.2.2    O    TLV-E    7-1503 */

    return uc.length;
}
