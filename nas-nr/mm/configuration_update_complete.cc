#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.20 Configuration update complete */
result_t de_configuration_update_complete(dissector                        d,
                                          context*                         ctx,
                                          configuration_update_complete_t* ret) {
    const use_context uc(&d, ctx, "configuration-update-complete", 0);
    de_nmm_header(d, ctx, &ret->header).step(d);

    /* No Data */

    return {uc.consumed()};
}
