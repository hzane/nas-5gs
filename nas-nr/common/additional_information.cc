#include "../common.hh"

// Additional information  9.11.2.1
extern const element_meta cmn::additional_inf = {
    0x24,
    "Additional information",
    cmn::dissect_additional_inf,
    nullptr,
};

const field_meta hf_additional_inf = {
    "Additional information",
    "nas.nr.cmn.additional_info",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// Additional information  9.11.2.1
int cmn::dissect_additional_inf(dissector d, context* ctx) {
    // The coding of the additional information value is dependent on the LCS application.
    diag("no dissect for %s\n", paths(ctx).c_str());

    auto i = d.add_item(d.length, &hf_additional_inf, enc::na);
    d.step(d.length);
    unused(i);

    return d.length;
}
