#include "../common/dissector.hh"
#include "../common/context.hh"
#include "../common/use_context.hh"
#include "../common/core.hh"

int dissect_selected_eps_security_algo(dissector d, context* ctx) {
    diag("no dissect %s\n", join(ctx->paths).c_str());
    return d.length;
}
