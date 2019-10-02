#include "context.hh"
#include "dissector.hh"
#include "use_context.hh"

// RFC2284 RFC3748

/* 9.11.2.2    EAP message*/
int dissect_eap_message(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "EAP", 0);

    /* EAP message as specified in IETF RFC 3748 */


    return uc.length;
}

