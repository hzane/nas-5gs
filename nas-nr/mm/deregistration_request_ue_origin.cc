#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.12 De-registration request (UE originating de-registration)  */
int dissect_deregistration_request_ue_origin(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "de-reg-ue-orig", 0);
    // UE to network
    up_link(d.pinfo);

    return uc.length;
}
