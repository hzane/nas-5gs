#include "../common/ies.hh"
#include "context.hh"
#include "dissector.hh"
#include "use_context.hh"

// 9.11.2.7	N1 mode to S1 mode NAS transparent container
result_t die_n1_mode_to_s1_mode_container(dissector                       d,
                                          context*                        ctx,
                                          n1_mode_to_s1_mode_container_t* ret) {
    const use_context uc(&d, ctx, "n1-mode-to-s1-mode-container", 0);

    de_uint8(d, ctx, &ret->seq_no).step(d);
    return {uc.consumed()};
}
