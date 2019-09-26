#include "context.hh"
#include "dissector.hh"
#include "use_context.hh"

// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int dissect_n1_to_s1_mode_container(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "n1-mode-to-s1-mode-transparent-container",0);

    return uc.length;
}

