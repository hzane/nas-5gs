#include "../common/use_context.hh"
#include "buff_view.hh"
#include "common.hh"
#include "formats.hh"

/* * 3GPP TS 24.008 g10 10.5.7.4 */
// can only be used in opt_elem_tlv
int dissect_gprs_timer2_set(dissector d, context *ctx) {
    const use_context uc(ctx, "gprs-timer2", d, -1);
    d.set_item(1, gprs_timer_2_string(d.uint8()));

    return 1;
}
