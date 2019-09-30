#include "../common/use_context.hh"
#include "common.hh"
#include "formats.hh"

// 3GPP TS 24.008 g10

// can only be used in opt_elem_tlv
int dissect_gprs_timer_set(dissector d, context *ctx) {
    const use_context uc(ctx, "gprs-timer", d, -1);

    d.set_item(1, gprs_timer_string(d.uint8()));

    /* no length check possible */
    return 1;
}
