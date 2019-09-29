#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

extern const element_meta mm::selected_eps_security_algo = {
    0x57,
    "EPS NAS security algorithms - Selected EPS NAS security algorithms",
    dissect_selected_eps_security_algo,
};
int mm::dissect_selected_eps_security_algo(dissector d, context* ctx) {
    diag("no dissect %s\n", ctx->path().c_str());
    return d.length;
}

