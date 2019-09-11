#include "../dissect_mm_msg.hh"

extern const element_meta mm::selected_eps_security_algo = {
    0x57,
    "EPS NAS security algorigthms - Selected EPS NAS security algorithms",
    dissect_selected_eps_security_algo,
    nullptr,
};
int mm::dissect_selected_eps_security_algo(dissector d, context* ctx) {
    diag("no dissect %s\n", ctx->path().c_str());
    return d.length;
}
