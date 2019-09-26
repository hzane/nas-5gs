#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*8.2.21 Identity request */
int dissect_identity_request(dissector d, context* ctx) {
    use_context uc(ctx, "identity-request", d, -1);
    // AMF to UE
    down_link(d.pinfo);
    return 1;
}
