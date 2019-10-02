#include "../common/dissector.hh"
#include "../common/use_context.hh"


/* 9.11.3.53A   UE parameters update transparent container */
int dissect_ue_parameters_update_transparent_container(dissector d, context*ctx) {
    const use_context uc(&d, ctx, "ue-parameters-update-transprent-container", -1);

    return d.length;
}
