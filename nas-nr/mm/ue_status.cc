#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;

// 9.11.3.56
int mm::dissect_ue_status(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-status", d, -1);

    static const field_meta* flags[] = {
        &hf_5gmm_registration_status,
        &hf_emm_registration_status,
        nullptr,
    };
    /* 0     0     0     0     0     0 Spare    S1  mode reg */
    d.add_bits(flags);
    return 1;
}

/*    9.11.3.56    UE status */
const tf_string cmn::tfs_ue_status_n1_mode = {
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};

// 5GMM registration status (N1 mode reg) (octet 3, bit 2)
const field_meta cmn::hf_5gmm_registration_status = {
    "5GMM registration status (N1 mode reg)",
    "nas.nr.registration.status.n1",
    ft::ft_boolean,
    8,
    nullptr,
    &cmn::tfs_ue_status_n1_mode,
    nullptr,
    0x02,

};

const field_meta cmn::hf_emm_registration_status = {
    "EMM registration status (S1 mode reg)",
    "nas.nr.registration.status.s1",
    ft::ft_boolean,
    8,
    nullptr,
    &cmn::tfs_emm_registration_status,
    nullptr,
    0x01,

};
