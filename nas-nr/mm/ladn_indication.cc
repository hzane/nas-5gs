#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.29    LADN indication  */
int dissect_ladn_indication(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "ladn-indication", 0);
    return uc.length;
}
