#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

extern const element_meta mm::mico_indication = {
    0xb0,
    "MICO indication",
    dissect_mico_ind,
    nullptr,
};


/*  9.11.3.31    MICO indication */
int mm::dissect_mico_ind(dissector d, context* ctx) {
    const use_context uc(ctx, "mico-indication", d, -1);

    auto i = d.add_item(1, &hfm_mm_raai_b0, enc::be);

    // In the UE to network direction bit 1 is spare. The UE shall set this bit to
    // zero. In the network to UE and the UE to network direction:
    (void) d.add_item(1, &hf_mm_sprti, enc::be);

    return 1;
}

struct mico_indication_t {
    uint8_t raai;
    uint8_t sprti;
};

const tf_string tfs_raai = {
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};

const field_meta mm::hfm_mm_raai_b0 = {
    "Registration Area Allocation Indication (RAAI)",
    "nas.nr.mm.raai",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_raai,
    nullptr,
    0x01,
};

// In the network to UE and the UE to network direction:
const tf_string tfs_sprti = {
    "strictly periodic registration timer supported",
    "strictly periodic registration timer not supported",
};

// In the network to UE and the UE to network direction:
const field_meta mm::hf_mm_sprti = {
    "Strictly Periodic Registration Timer Indication (SPRTI)",
    "nas.nr.mm.sprti",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_sprti,
    nullptr,
    0x02,
};
