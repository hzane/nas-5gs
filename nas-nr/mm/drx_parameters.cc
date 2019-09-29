#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

/* 9.11.3.2A    5GS DRX parameters*/
const tag_field hf_drx_param = {
    "DRX value",
    0x0f,
    (const v_string[]){
        {0x0, "DRX value not specified"},
        {0x1, "DRX cycle parameter T = 32"},
        {0x2, "DRX cycle parameter T = 64"},
        {0x3, "DRX cycle parameter T = 128"},
        {0x4, "DRX cycle parameter T = 256"},
        {0, nullptr},
    },
};

// DRX parameters 9.11.3.2A
int mm::dissect_drx_parameter(dissector d, context* ctx) {
    const use_context uc(ctx, "DRX parameters", d, -1);

    (void) d.add_item(&hf_drx_param);
    d.step(1);

    return 1;
}



