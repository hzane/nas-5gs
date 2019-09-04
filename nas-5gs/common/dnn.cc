#include "common.hh"

const field_meta cmn::hf_dnn = {
    "DNN",
    "nas_5gs.cmn.dnn",
    ft::ft_bytes,
    fd::bstrn,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

/*  9.11.2.1A    DNN */
int cmn::dissect_dnn(dissector d, context* ctx) {
    use_context uc(ctx, "DNN", d, 0);

    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */
    // auto str = bstrn_string(d.safe_ptr(), d.safe_length(-1));

    /* Highlight bytes including the first length byte */
    auto item = d.add_item(d.length, &hf_dnn, enc::be);
    d.step(d.length);

    // d.extraneous_data_check(0);
    return uc.length;
}
