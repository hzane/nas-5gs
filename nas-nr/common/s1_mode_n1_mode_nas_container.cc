#include "../common.hh"


int cmn::dissect_s1_to_n1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "s1-mode-to-n1-mode-transparent-container", d, 2);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/
    (void) d.add_item(4, &hf_authentication_code, enc::be);
    d.step(4);

    (void) d.add_item(1, &hf_integrity_algo_type, enc::be);
    (void) d.add_item(1, &hf_ciphering_algo_type, enc::be);
    d.step(1);

    (void) d.add_item(1, &hf_ksi_5g, enc::be);
    (void) d.add_item(1, &hf_security_context_type, enc::be);
    (void) d.add_item(1, &hf_next_hop_chaining_counter, enc::be);
    d.step(1);

    // oct 9-10 is spare
    d.step(2);

    return uc.length;
}

namespace cmn {
const true_false_string tfs_emm_registration_status = {
    "UE is in EMM-REGISTERED state",
    "UE is not in EMM-REGISTERED state",
};

const field_meta hf_authentication_code = {
    "Message authentication code",
    "nas.nr.cmn.mac",
    ft::ft_uint32,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

// Next hop chaining counter (see 3GPP TS 33.501 [24])
const field_meta hf_next_hop_chaining_counter = {
    "Next hop chaining counter (NCC)",
    "nas.nr.cmn.ncc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x70u,
};
}
