#include "dissector.hh"
#include "nas.hh"
#include "use_context.hh"

/*  9.11.2.1A    DNN */
int dissect_dnn(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "dnn", 0);

    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */

    /* Highlight bytes including the first length byte */
    // (void) d.add_item(d.length, &hf_dnn, enc::be);
    // d.step(d.length);

    return uc.length;
}
