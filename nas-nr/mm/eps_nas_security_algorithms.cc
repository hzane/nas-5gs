#include "../common/dissector.hh"
#include "../common/use_context.hh"

int dissect_selected_eps_security_algo(dissector d, context* ctx) {
    diag("no dissect %s\n", ctx->path().c_str());
    return d.length;
}
