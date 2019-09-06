#include "../common.hh"


int cmn::dissect_s1_to_n1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "s1-mode-to-n1-mode-transparent-container", d, 2);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/
    auto i = d.add_item(4, &hf_msg_auth_code, enc::be);
    d.step(4);

    i = d.add_item(1, &hf_int_prot_algo_type, enc::be);
    i = d.add_item(1, &hf_ciphering_algo_type, enc::be);
    d.step(1);

    i = d.add_item(1, &hf_ksi_5g, enc::be);
    i = d.add_item(1, &hf_tsc, enc::be);
    i = d.add_item(1, &hf_ncc, enc::be);
    d.step(1);

    unused(i);

    // oct 9-10 is spare
    d.step(2);

    return uc.length;
}

namespace cmn {
const true_false_string tfs_nas_5gs_mm_s1_mod = {
    "UE is in EMM-REGISTERED state",
    "UE is not in EMM-REGISTERED state",
};

const field_meta hf_msg_auth_code = {
    "Message authentication code",
    "nas_5gs.cmn.mac",
    ft::ft_uint32,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

// Next hop chaining counter (see 3GPP TS 33.501 [24])
const field_meta hf_ncc= {
    "NCC",
    "",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x70u,
};

}

const field_meta cmn::hf_mm_s1_mode_reg_b0 = {
    "S1 mode reg",
    "nas_5gs.mm.s1_mode_reg_b0",
    ft::ft_boolean,
    8,
    nullptr,
    &tfs_nas_5gs_mm_s1_mod,
    nullptr,
    0x01,

};
