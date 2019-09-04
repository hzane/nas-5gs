#include "common.hh"

namespace {
/* *    9.11.3.56    UE status */
const true_false_string tfs_nas_5gs_mm_n1_mod = {
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};

const field_meta hf_n1_to_s1_mode = {
    "N1 mode to S1 mode NAS transparent container",
    "n1_mode_2_s1_mode_container",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};
} // namespace

const field_meta cmn::hf_mm_n1_mode_reg_b1 = {
    "N1 mode reg",
    "nas_5gs.mm.n1_mode_reg_b1",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas_5gs_mm_n1_mod,
    nullptr,
    0x02,

};

// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int cmn::dissect_n1_to_s1_mode_container(dissector d, context* ctx) {
    // a type 3 information element with a length of 2 octets
    d.add_item(2, &hf_n1_to_s1_mode, enc::be);
    return d.length;
}
