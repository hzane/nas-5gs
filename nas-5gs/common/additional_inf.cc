#include "../common.hh"

// Additional information  9.11.2.1
extern const element_meta cmn::additional_inf = {
    0x24,
    "Additional information",
    dissect_additional_inf,
    nullptr,
};


// Additional information  9.11.2.1
int cmn::dissect_additional_inf(dissector d, context* ctx) {
    // The coding of the additional information value is dependent on the LCS application.
    diag("no dissect for %s\n", paths(ctx).c_str());
    return d.length;
}
