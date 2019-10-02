#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.25 Security mode command  */
int dissect_security_mode_command(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "security-mode-cmd", 0);

    /* Direction: network to UE */
    down_link(d.pinfo);

    return uc.length;
}
