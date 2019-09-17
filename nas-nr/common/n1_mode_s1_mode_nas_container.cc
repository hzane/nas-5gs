#include "../common.hh"


// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int cmn::dissect_n1_to_s1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "n1-mode-to-s1-mode-transparent-container", d, 0);
    auto i = d.add_item(1, &hf_sequence_no, enc::be);
    d.step(1);

    unused(i);

    return uc.length;
}

struct n1_to_s1_mode_container_t {
    uint8_t sequence_no;
};

namespace cmn {
/* *    9.11.3.56    UE status */
const true_false_string tfs_ue_status_n1_mode = {
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};

const field_meta hf_sequence_no        = {
    "Sequence number","nas.nr.mm.sequence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};

const field_meta hf_n1_to_s1_mode = {
    "N1 mode to S1 mode NAS transparent container",
    "n1.mode.s1.container",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};
} // namespace

// 5GMM registration status (N1 mode reg) (octet 3, bit 2)
const field_meta cmn::hf_5gmm_registration_status = {
    "5GMM registration status (N1 mode reg)",
    "nas.nr.5gmm.n1.mode.reg.b1",
    ft::ft_boolean,
    8,
    nullptr,
    &cmn::tfs_ue_status_n1_mode,
    nullptr,
    0x02,

};
