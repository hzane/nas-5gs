#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;

extern const field_meta hf_dcni;
extern const field_meta hf_nssci;

//  9.11.3.36    Network slicing indication
int mm::dissect_network_slicing_indicationication(dissector d, context* ctx) {
    const use_context uc(ctx, "nw-slicing-indication", d, -1);

    static const field_meta* flags[] = {
        // &hf_spare_b3,
        // &hf_spare_b2,
        &hf_dcni,
        &hf_nssci,
        nullptr,
    };
    d.add_bits(flags);
    d.step(1);

    return 1;
}

struct network_slicing_indication_t {
    uint8_t dcni;
    uint8_t nssci;
};

// Network slicing indication  9.11.3.36
extern const element_meta mm::network_slicing_indication = {
    0x90,
    "Network slicing indication",
    mm::dissect_network_slicing_indicationication,
    nullptr,
};

/* 9-  Network slicing indication  Network slicing indication 9.11.3.36  O  TV 1 */
const true_false_string tfs_dcni = {
    "Requested NSSAI created from default configured NSSAI",
    "Requested NSSAI not created from default configured NSSAI",
};

const field_meta hf_dcni = {
    "Default configured NSSAI indication (DCNI)",
    "nas.nr.mm.dcni",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_dcni,
    nullptr,
    0x02,
};

const true_false_string tfs_changed_not_changed = {
    "Changed",
    "Not Changed",
};

const field_meta        hf_nssci                = {
    "Network slicing subscription change indication (NSSCI)",
    "nas.nr.mm.nssci",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_changed_not_changed,
    nullptr,
    0x01,
};
