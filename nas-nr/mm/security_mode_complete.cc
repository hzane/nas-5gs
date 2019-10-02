#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.26 Security mode complete */
int dissect_security_mode_complete(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "security-mode-complete", 0);
    // UE to network
    up_link(d.pinfo);

    return uc.length;
}
