#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
// 9.11.3.37A NSSAI inclusion mode page.381
// a type 1 information element
int mm::dissect_nssai_inclusion_mode(dissector d, context* ctx) {
    const use_context        uc(ctx, "nssai-inclusion-mode", d, -1);

    d.add_item(&hf_nssai_inc_mode);

    return 1;
}


/* 9.11.3.37A   NSSAI inclusion mode */
const tag_field mm::hf_nssai_inc_mode = {
    "NSSAI inclusion mode",
    0x03,
    (const v_string[]){
        {0x00, "A"},
        {0x01, "B"},
        {0x02, "C"},
        {0x03, "D"},
        {0, nullptr},
    },
};
