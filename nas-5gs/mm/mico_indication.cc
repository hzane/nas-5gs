#include "../dissect_mm_msg.hh"

//  MICO indication    9.11.3.31
int dissect_mico_ind(dissector d, context* ctx = nullptr);

extern const element_meta mm::mico_ind = {
    0xb0,
    "MICO indication",
    dissect_mico_ind,
    nullptr,
};

/* 9.11.3.31    MICO indication */
static const true_false_string tfs_nas_5gs_raai = {
    // NOLINT: unused-const-variable
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};


/*  9.11.3.31    MICO indication */
static const true_false_string tfs_raai = {
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};

/*  9.11.3.31    MICO indication */
int mm::dissect_mico_ind(dissector d, context* ctx) {
    auto len = d.length;

    d.add_item(1, hf_mm_raai_b0, enc::be);

    // In the UE to network direction bit 1 is spare. The UE shall set this bit to
    // zero. In the network to UE and the UE to network direction:
    d.add_item(1, &hf_mm_sprti, enc::be);
    return 1;
}
