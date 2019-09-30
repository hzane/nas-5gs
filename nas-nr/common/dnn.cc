#include "../common/use_context.hh"
#include "common.hh"
#include "formats.hh"

/*  9.11.2.1A    DNN */
int dissect_dnn(dissector d, context* ctx) {
    const use_context uc(ctx, "dnn", d, 0);

    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */
    d.set_item(d.length, apn_string(d.ptr(), d.length));
    d.step(d.length);

    return uc.length;
}

// DNN 9.11.2.1A
extern const element_meta dnn = {
    0x25,
    "DNN",
    dissect_dnn,
};
