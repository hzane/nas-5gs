#include "../common.hh"


// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int cmn::dissect_n1_to_s1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "n1-mode-to-s1-mode-transparent-container", d, 0);
    auto i = d.add_item(1, &hf_seq_no, enc::be);
    d.step(1);

    unused(i);

    return uc.length;
}


namespace cmn {
/* *    9.11.3.56    UE status */
const true_false_string tfs_nas_5gs_mm_n1_mod = {
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};
const field_meta hf_sqs_no        = {
    "Sequence number","",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
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
    "nas.nr.mm.n1_mode_reg_b1",
    ft::ft_boolean,
    8,
    nullptr,
    &cmn::tfs_nas_5gs_mm_n1_mod,
    nullptr,
    0x02,

};
