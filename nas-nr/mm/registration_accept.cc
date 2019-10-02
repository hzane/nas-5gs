#include "../common/core.hh"
#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.7    Registration accept */
int dissect_registration_accept(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "registration-accept", 12);
    return uc.length;
}


// EAP message  9.11.2.2
int dissect_eap_message(dissector d, context* ctx = nullptr);

//  Operator-defined access category definitions 9.11.3.38
int dissect_operator_defined_acd(dissector d, context* ctx );

/* 9.10.2.2     EAP message*/
/* EAP message as specified in IETF RFC 3748 */
int dissect_eap_message(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "eap", -1);

    diag("eap message specified in rfc 3748\n");
    return d.length;
}

/* 9.11.3.38    Operator-defined access category definitions */
int dissect_operator_defined_acd(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "operator-defined-access-category-definitions", 0);
    return uc.length;
}
