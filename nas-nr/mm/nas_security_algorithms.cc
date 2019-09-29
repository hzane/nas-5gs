#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;


const tag_field hf_security_ciphering_algo = {
    "Type of ciphering algorithm",
    0xf0,
    (const v_string[]){
        {0x0, "5G-EA0 (null ciphering algorithm)"},
        {0x1, "128-5G-EA1"},
        {0x2, "128-5G-EA2"},
        {0x3, "128-5G-EA3"},
        {0x4, "5G-EA4"},
        {0x5, "5G-EA5"},
        {0x6, "5G-EA6"},
        {0x7, "5G-EA7"},
        {0, nullptr},
    },
};


/* *   9.11.3.34    NAS security algorithms */
const tag_field hf_security_integrity_algo = {
    "Type of integrity protection algorithm",
    0x0f,
    (const v_string[]){
        {0x0, "5G-IA0 (null integrity protection algorithm)"},
        {0x1, "128-5G-IA1"},
        {0x2, "128-5G-IA2"},
        {0x3, "128-5G-IA3"},
        {0x4, "5G-IA4"},
        {0x5, "5G-IA5"},
        {0x6, "5G-IA6"},
        {0x7, "5G-IA7"},
        {0, nullptr},
    },
};

/* *   9.11.3.34    NAS security algorithms */
int mm::dissect_security_algo(dissector d, context* ctx) {
    const use_context uc(ctx, "sec-algo", d, -1);

    d.add_item(&hf_security_ciphering_algo);
    d.add_item(&hf_security_integrity_algo);
    return 1;
}



