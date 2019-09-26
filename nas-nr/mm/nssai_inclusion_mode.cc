#include "../common/dissector.hh"
#include "../common/use_context.hh"

// 9.11.3.37A NSSAI inclusion mode page.381
// a type 1 information element
int dissect_nssai_inclusion_mode(dissector d, context* ctx) {
    const use_context        uc(ctx, "nssai-inclusion-mode", d, -1);

    return 1;
}
