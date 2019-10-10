#include "../common/dissector.hh"
#include "../common/use_context.hh"
#include "../common/messages.hh"

/* 9.11.3.37    NSSAI */
int dissect_configured_nssai(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "configured-nssai", 0);

    return uc.length;
}

/* 9.11.3.37    NSSAI
 * S-NSSAI value is coded as the length and value part of S-NSSAI information element
as specified in subclause 9.11.2.8 starting with the second octet.
 */
int dissect_allowed_nssai(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "allowed-nssai", 0);
    return uc.length;
}

/* 9.11.3.37    NSSAI*/
int dissect_requested_nssai(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "requested-nssai", 0);

    return uc.length;
}
