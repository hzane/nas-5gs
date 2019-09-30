#include "../common/dissect_mm_msg.hh"


using namespace nas;
using namespace mm;

int mm::dissect_selected_eps_security_algo(dissector d, context* ctx) {
    diag("no dissect %s\n", ctx->path().c_str());
    return d.length;
}
