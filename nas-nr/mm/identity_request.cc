#include "../common/dissector.hh"
#include "../common/context.hh"
#include "../common/use_context.hh"

/*8.2.21 Identity request */
int dissect_identity_request(dissector d, context* ctx) {
    use_context uc(&d, ctx, "identity-request", -1);
    // AMF to UE
    down_link(d.pinfo);
    return 1;
}
