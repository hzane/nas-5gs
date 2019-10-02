#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.18    Configuration update indication */
int dissect_configuration_update_indication(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "configuration-update-indication", -1);

    return 1;
}
