#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;
// 9.11.3.9A 5GS update type
const element_meta mm::update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
    nullptr,
};


// 9.11.3.9A 5GS update type
int mm::dissect_update_type(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gs-update-type", d, -1);

    static const field_meta* flags[] = {
        // &nas::hf_spare_b3,
        &hf_preferred_network_behaviour,
        &hf_ngran_radio_capability_update,
        &hf_sms_requested,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

struct update_type_t{
    uint8_t pnb_ciot;
    uint8_t ng_ran_rcu;
    uint8_t sms_requested;
};
