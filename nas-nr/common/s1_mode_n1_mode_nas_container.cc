#include "context.hh"
#include "dissector.hh"
#include "use_context.hh"

int dissect_s1_to_n1_mode_container(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "s1-mode-to-n1-mode-transparent-container", 2);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/


    return uc.length;
}
