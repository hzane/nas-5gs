#include "../common.hh"


// 9.11.2.7 N1 mode to S1 mode NAS transparent container page.350
int cmn::dissect_n1_to_s1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "n1-mode-to-s1-mode-transparent-container", d, 0);
    (void) d.add_item(1, &hf_sequence_no, enc::be);
    d.step(1);

    return uc.length;
}

namespace cmn {

const field_meta hf_sequence_no = {
    "Sequence number",
    "nas.nr.mm.sequence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};

} // namespace
