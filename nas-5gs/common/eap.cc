#include "common.hh"

const field_meta cmn::hf_eap = {
    "EAP",
    "nas_5gs.eap",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// RFC2284 RFC3748
/* 9.11.2.2    EAP message*/
int cmn::dissect_eap_msg(dissector d, context* ctx) {
    use_context uc(ctx, "EAP", d, 0);
    /* EAP message as specified in IETF RFC 3748 */
    d.add_item(d.length, &hf_eap, enc::na);
    d.step(d.length);

    return uc.length;
}
