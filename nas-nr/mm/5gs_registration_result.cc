#include "../dissect_mm_msg.hh"


// 9.11.3.6    5GS registration result
int mm::dissect_registration_result(dissector d, context* ctx) {
    use_context uc(ctx, "5gs-registration-result", d, -1);

    /* 0 Spare 0 Spare 0 Spare 0 Spare SMS allowed 5GS registration result value */
    auto i = d.add_item(1, &hf_reg_res_sms_allowed, enc::be);
    i = d.add_item(1, &hf_registration_result, enc::be);
    d.step(1);

    unused(i);
    return 1;
}

namespace mm {

/* 9.11.3.6    5GS registration result */
const value_string nas_5gs_mm_reg_res_values[] = {
    {0x1, "3GPP access"},
    {0x2, "Non-3GPP access"},
    {0x3, "3GPP access and non-3GPP access"},
    {0, nullptr},
};
const field_meta hf_registration_result = {
    "5GS registration result",
    "nas_5gs.mm.registration.result",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_reg_res_values,
    nullptr,
    nullptr,
    0x07,
};
}

const element_meta mm::registration_result = {
    0xff,
    "5GS registration result",
    dissect_registration_result,
    nullptr,
};

