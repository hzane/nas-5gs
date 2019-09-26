#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.37    NSSAI */
int dissect_configured_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "configured-nssai", d, 0);

    return uc.length;
}

/* 9.11.3.37    NSSAI
 * S-NSSAI value is coded as the length and value part of S-NSSAI information element
as specified in subclause 9.11.2.8 starting with the second octet.
 */
int dissect_allowed_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "allowed-nssai", d, 0);
    return uc.length;
}

/* 9.11.3.37    NSSAI*/
int dissect_requested_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "requested-nssai", d, 0);

    return uc.length;
}
