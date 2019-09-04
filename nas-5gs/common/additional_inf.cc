#include "common.hh"

// Additional information  9.11.2.1
extern const element_meta cmn::additional_inf = {
    0x24,
    "Additional information",
    dissect_additional_inf,
    nullptr,
};

/* 9.10.2.1    Additional information*/
int cmn::dissect_additional_inf(dissector d, context* ctx) {
    diag("no dissect for %s\n", paths(ctx).c_str());
    return d.length;
}
