#include "../common/dissector.hh"
#include "../common/use_context.hh"


/*  8.2.14 De-registration request (UE terminated de-registration) */
int dissect_deregistration_request_ue_terminate(dissector d, context* ctx) {
    const use_context uc(ctx, "de-registration-request-ue-term", d, 0);
    // network to UE
    down_link(d.pinfo);

    return uc.length;
}
