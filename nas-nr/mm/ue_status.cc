#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace nas;

// 5GMM registration status (N1 mode reg) (octet 3, bit 2)
inline const bool_field hf_5gmm_registration_status = {
    "5GMM registration status (N1 mode reg)",
    0x02,
    "UE is not in 5GMM-REGISTERED state",
    "UE is in 5GMM-REGISTERED state",
};

const bool_field hf_emm_registration_status = {
    "EMM registration status (S1 mode reg)",
    0x01,
    "UE is not in EMM-REGISTERED state",
    "UE is in EMM-REGISTERED state",
};

// 9.11.3.56
int mm::dissect_ue_status(dissector d, context* ctx) {
    const use_context        uc(ctx, "ue-status", d, -1);

    /* 0     0     0     0     0     0 Spare    S1  mode reg */

    d.add_item(&hf_5gmm_registration_status);
    d.add_item(&hf_emm_registration_status);
    return 1;
}



