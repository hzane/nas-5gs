#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

/*  9.11.4.16    SSC mode */
const tag_field hf_ssc_mode = {
    "SSC mode",
    0x07,
    (const v_string[]){
        {0x1, "SSC mode 1"},
        {0x2, "SSC mode 2"},
        {0x3, "SSC mode 3"},
        {0x4, "SSC mode 1"},
        {0x5, "SSC mode 2"},
        {0x6, "SSC mode 3"},
        {0, nullptr},
    },
};

/*  9.11.4.16    SSC mode */
int sm::dissect_ssc_mode(dissector d, context* ctx) {
    const use_context uc(ctx, "ssc-mode", d, -1);

    (void) d.add_item(&hf_ssc_mode);

    return 1;
}

