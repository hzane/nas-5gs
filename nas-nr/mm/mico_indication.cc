#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.31    MICO indication */
int dissect_mico_ind(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "mico-indication", -1);

    return 1;
}
