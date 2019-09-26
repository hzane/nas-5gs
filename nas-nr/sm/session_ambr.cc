#include "../common/dissector.hh"
#include "../common/use_context.hh"


// 9.11.4.14    Session-AMBR
int dissect_session_ambr(dissector d, context* ctx) {
    const use_context uc(ctx, "session-ambr", d, 0);

    /* Unit for Session-AMBR for downlink octet 3*/
    /* Session-AMBR for downlink (octets 4 and 5) */

    return uc.length;
}
