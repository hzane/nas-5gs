#include "common.hh"

// Additional information  9.11.2.1
extern const element_meta additional_information = {
    0x24,
    "Additional information",
    dissect_additional_information,
};

const octet_field hf_additional_information = {
    "Additional information",
};

// Additional information  9.11.2.1
int dissect_additional_information(dissector d, context* ctx) {
    // The coding of the additional information value is dependent on the LCS application.
    diag("no dissect for %s\n", paths(ctx).c_str());

    (void) d.add_item(&hf_additional_information, d.length, true);

    return d.length;
}
