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
    const use_context uc(ctx, "DNN", d, 0);

    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */
    // auto str = bstrn_string(d.safe_ptr(), d.safe_length(-1));

    /* Highlight bytes including the first length byte */
    auto item = d.add_item(d.length, &hf_dnn, enc::be);
    d.step(d.length);

    return uc.length;
}

// DNN 9.11.2.1A
extern const element_meta cmn::dnn = {
    0x25,
    "DNN",
    dissect_dnn,
    nullptr,
};
