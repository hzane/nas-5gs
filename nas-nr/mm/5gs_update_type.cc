#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;
// 9.11.3.9A 5GS update type
const element_meta mm::update_type = {
    0x53,
    "5GS update type",
    dissect_update_type,
};


// 9.11.3.9A 5GS update type
int mm::dissect_update_type(dissector d, context* ctx) {
    const use_context        uc(ctx, "5gs-update-type", d, -1);

    d.add_item(&hf_preferred_network_behaviour);
    d.add_item( &hf_ngran_radio_capability_update);
    d.add_item(&hf_sms_requested);
    d.step(1);

    return 1;
}
