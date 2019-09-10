#include "../common.hh"


// 9.11.2.6 Intra N1 mode NAS transparent container page.349
int cmn::dissect_intra_n1_mode_container(dissector d, context* ctx) {
    use_context uc(ctx, "intra-n1-mode-nas-transparent-container", d, 0);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/
    auto i = d.add_item(4, &hf_msg_auth_code, enc::be);
    d.step(4);

    (void) d.add_item(1, &hf_int_prot_algo_type, enc::be);
    (void) d.add_item(1, &hf_ciphering_algo_type, enc::be);
    d.step(1);

    (void) d.add_item(1, &hf_ksi_5g, enc::be);
    (void) d.add_item(1, &hf_tsc, enc::be);
    (void) d.add_item(1, &hf_kacf, enc::be);
    d.step(1);

    (void) d.add_item(1, &hf_seq_no, enc::be);

    return uc.length;
}

namespace cmn {
// NAS security algorithms information element (see subclause 9.11.3.34
const field_meta hf_int_prot_algo_type = {
    "Type of integrity protection algorithm",
    "nas_5gs.cmn.int_prot_algo",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0fu,
};

const field_meta hf_tsc                = {
    "TSC",
    "nas_5gs.cmn.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x04u,
};
const true_false_string tfs_kacf = {
    "a new KAMF has been calculated by the network",
    "a new KAMF has not been calculated by the network",
};

const field_meta hf_kacf               = {
    "KACF","",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_kacf,
    nullptr,
    0x10u,
};
const field_meta hf_ksi_5g             = {
    "Key set identifier in 5G",
    "nas_5gs.cmn.ksi",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x07u,
};
const field_meta hf_ciphering_algo_type = {
    "Type of ciphering algorithm",
    "nas_5gs.cmn.ciphering.algo",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0u,
};
const field_meta hf_seq_no              = {
    "Sequence number", "",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};
}
