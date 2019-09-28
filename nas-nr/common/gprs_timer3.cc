#include "../common/use_context.hh"
#include "common.hh"
#include "format.hh"

/*  [10] 10.5.7.4a */
// can only be used in opt_elem_tlv
int cmn::dissect_gprs_timer3_set(dissector d, context *ctx) {
    use_context uc(ctx, "gprs-timer-3", d, -1);

    d.set_item(1, gprs_timer_3_string(d.uint8()));

    return 1;
}
