#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace mm;

/* 9.11.3.6    5GS registration result */
const tag_field hf_registration_result = {
    "5GS registration result",
    0x07,
    (const v_string[]){
        {0x1, "3GPP access"},
        {0x2, "Non-3GPP access"},
        {0x3, "3GPP access and non-3GPP access"},
        {0, nullptr},
    },
};
extern const bool_field hf_reg_res_sms_allowed;

// 9.11.3.6    5GS registration result
int mm::dissect_registration_result(dissector d, context* ctx) {
    use_context uc(ctx, "5gs-registration-result", d, -1);

    /* 0 Spare 0 Spare 0 Spare 0 Spare SMS allowed 5GS registration result value */
    auto i = d.add_item(&hf_reg_res_sms_allowed);
    i = d.add_item( &hf_registration_result);
    d.step(1);

    unused(i);
    return 1;
}



