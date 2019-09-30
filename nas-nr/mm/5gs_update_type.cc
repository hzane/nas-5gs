#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;


const bool_field       hf_ngran_radio_capability_update = {
    "NG-RAN Radio Capability Update (NG-RAN-RCU)",
    0x02,
    "Not Needed",
    "Needed",
};

const tag_field hf_preferred_network_behaviour = {
    "Preferred CIoT network behaviour (PNB-CIoT)",
    0,
    (const v_string[]){
        {0, "no additional information"},
        {1, "control plane CIot 5GS optimization"},
        {2, "user plane CIot 5GS optimization"},
        {3, "reserved"},
        {0, nullptr},
    },
};


const bool_field hf_sms_requested = {
    "SMS requested",
    0x01,
    {
        "SMS over NAS supported",
        "SMS over NAS not supported",
    },
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
