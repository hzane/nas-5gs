#include "../dissect_mm_msg.hh"

extern const element_meta mm::mico_ind = {
    0xb0,
    "MICO indication",
    dissect_mico_ind,
    nullptr,
};


/*  9.11.3.31    MICO indication */
int mm::dissect_mico_ind(dissector d, context* ctx) {
    const use_context uc(ctx, "mico-indication", d, -1);    

    auto i = d.add_item(1, hf_mm_raai_b0, enc::be);

    // In the UE to network direction bit 1 is spare. The UE shall set this bit to
    // zero. In the network to UE and the UE to network direction:
    i = d.add_item(1, &hf_mm_sprti, enc::be);

    unused(i);
    return 1;
}

const true_false_string tfs_raai = {
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};

const field_meta mm::hfm_mm_raai_b0 = {
    "Registration Area Allocation Indication (RAAI)",
    "nas_5gs.mm.raai_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_raai,
    nullptr,
    0x01,
};
const field_meta* mm::hf_mm_raai_b0 = &hfm_mm_raai_b0;

// In the network to UE and the UE to network direction:
const true_false_string tfs_sprti = {
    "strictly periodic registration timer supported",
    "strictly periodic registration timer not supported",
};

// In the network to UE and the UE to network direction:
const field_meta mm::hf_mm_sprti = {
    "Strictly Periodic Registration Timer Indication (SPRTI)",
    "nas_5gs.mm.sprti",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_sprti,
    nullptr,
    0x02,
};
