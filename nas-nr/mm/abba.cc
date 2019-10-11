#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/* 9.11.3.10    ABBA */
// 3GPP TS 33.501
result_t die_abba(dissector d, context* ctx, abba_t* ret) {
    // indicate set of security features defined for 5GS as described in 3GPP TS 33.501
    // [24].
    return de_octet(d, ctx, ret);
}
