#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace mm;

// 9.11.3.7	5GS registration type

const tag_field hf_registration_type = {
    "5GS registration type",
    0x07,
    (const v_string[]){
        {0x1, "initial registration"},
        {0x2, "mobility registration updating"},
        {0x3, "periodic registration updating"},
        {0x4, "emergency registration"},
        {0x7, "reserved"},
        {0, nullptr},
    },
};

const bool_field hf_follow_on_request = {
    "Follow-On Request bit (FOR)",
    0x08,
    {
        "Follow-on request pending",
        "No follow-on request pending",
    },
};


/* 9.11.3.7    5GS registration type */
int mm::dissect_registration_requestuest_type(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-registration-type", d, -1);

    d.add_item(&hf_follow_on_request);
    d.add_item(&hf_registration_type);

    return 1;
}
