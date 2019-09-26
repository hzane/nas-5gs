#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.4.8 Mapped EPS bearer contexts */
int dissect_eps_parameters(dissector d, int i, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);

    /* EPS parameter identifier */

    /*length of the EPS parameter contents field */

    return d.offset - uc.offset;
}

// Mapped EPS  bearer contexts     9.11.4.8
int dissect_mapped_eps_bearer_contexts(dissector d, context* ctx) {
    const use_context uc(ctx, "mapped-eps-bearer-contexts", d, 0);

    return uc.length;
}
