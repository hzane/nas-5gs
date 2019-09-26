#include "../common/dissector.hh"
#include "../common/use_context.hh"

// SOR transparent container   9.11.3.51
int dissect_sor_transparent_container(dissector d, context* ctx) {
    const use_context uc(ctx, "sor-transparent-container", d, 0);

    /* Layout differs depending on SOR data type*/
    return uc.length;
}
