#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;

/* 9-  Network slicing indication  Network slicing indication 9.11.3.36  O  TV 1 */
const bool_field hf_dcni = {
    "Default configured NSSAI indication (DCNI)",
    0x02,
    "Requested NSSAI not created from default configured NSSAI",
    "Requested NSSAI created from default configured NSSAI",
};

const bool_field        hf_nssci                = {
    "Network slicing subscription change indication (NSSCI)",
    0x01,
    "Not Changed",
    "Changed",
};

//  9.11.3.36    Network slicing indication
int mm::dissect_network_slicing_indicationication(dissector d, context* ctx) {
    const use_context uc(ctx, "nw-slicing-indication", d, -1);

    d.add_item(&hf_dcni);
    d.add_item(&hf_nssci);
    d.step(1);

    return 1;
}