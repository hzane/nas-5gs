#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// no body

result_t de_deregistration_accept_ue_orig(dissector                        d,
                                          context*                         ctx,
                                          deregistration_accept_ue_orig_t* ret) {
    const use_context uc(&d, ctx, "deregistration-accept-ue-orig", 0);
    // network to UE
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    return {uc.consumed()};
}