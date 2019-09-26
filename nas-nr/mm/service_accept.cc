#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.17 Service accept */
int dissect_service_accept(dissector d, context* ctx) {
    const use_context uc(ctx, "service-accept", d, 3);
    // network to UE
    down_link(d.pinfo);

    return uc.length;
}
