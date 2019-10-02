#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.11    Access type */
int dissect_access_type(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "access-type", -1);

    return 1;
}
