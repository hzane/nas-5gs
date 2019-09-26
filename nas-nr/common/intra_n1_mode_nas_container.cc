#include "context.hh"
#include "dissector.hh"
#include "use_context.hh"

// 9.11.2.6 Intra N1 mode NAS transparent container page.349
int dissect_intra_n1_mode_container(dissector d, context* ctx) {
    use_context uc(&d, ctx, "intra-n1-mode-nas-transparent-container", 0);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/


    return uc.length;
}

