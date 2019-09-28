#include "common.hh"
#include "../common/use_context.hh"

// RFC2284 RFC3748
/* 9.11.2.2    EAP message*/
int cmn::dissect_eap_message(dissector d, context* ctx) {
    const use_context uc(ctx, "EAP", d, 0);

    /* EAP message as specified in IETF RFC 3748 */

    return uc.length;
}

// EAP message 9.11.2.2
// as specified in IETF RFC 3748
const element_meta cmn::eap_message = {
    0x78,
    "EAP message",
    cmn::dissect_eap_message,
    nullptr,
};
