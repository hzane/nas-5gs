#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  8.2.27 Security mode reject */
int dissect_security_mode_reject(dissector d, context* ctx) {
    use_context uc(ctx, "security-mode-reject", d, -1);
    // UE to network
    up_link(d.pinfo);


    return 1;
}
