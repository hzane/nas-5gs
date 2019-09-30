#include "../common/use_context.hh"
#include "common.hh"
#include "formats.hh"

// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int dissect_n1_to_s1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "n1-mode-to-s1-mode-transparent-container", d, 0);

    d.add_item(1, "Sequence number", istring(d.uint8()));

    return uc.length;
}

