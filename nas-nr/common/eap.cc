#include "common.hh"
#include "../common/use_context.hh"

const field_meta cmn::hf_eap = {
    "EAP",
    "nas.nr.eap",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// RFC2284 RFC3748
/* 9.11.2.2    EAP message*/
int cmn::dissect_eap_message(dissector d, context* ctx) {
    const use_context uc(ctx, "EAP", d, 0);

    /* EAP message as specified in IETF RFC 3748 */
    (void) d.add_item(d.length, &hf_eap);
    d.step(d.length);

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
