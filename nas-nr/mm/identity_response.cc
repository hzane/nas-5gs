#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.22 Identity response  */
int dissect_identity_response(dissector d, context* ctx) {
    const use_context uc(ctx, "identity-response", d, 0);
    // UE to AMF
    up_link(d.pinfo);

    return uc.length;
}
