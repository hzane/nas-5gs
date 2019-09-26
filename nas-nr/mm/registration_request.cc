#include "../common/dissector.hh"
#include "../common/use_context.hh"


/* * 8.2.6 Registration request */
int dissect_registration_request(dissector d, context* ctx) {
    const use_context uc(ctx, "registration-request", d, -1);

    // UE to network
    up_link(d.pinfo);
    // get private data

    return uc.length;
}
