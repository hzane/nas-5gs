#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// 9.11.3.35	Network name
int mm::dissect_short_name_network(dissector d, context* ctx) {
    return dissect_full_name_network(d, ctx);
}


const bool_field hf_extension = {
    "Extension",
    0x80,
    "No Extension",
    "Extended",
};


const tag_field hf_coding_scheme = {
    "Coding Scheme",
    0x70,
    (const v_string[]){
        {0,
            "Cell Broadcast data coding scheme, GSM default alphabet, language unspecified, "
            "defined in 3GPP TS 23.038",
        },
        {1, "UCS2 (16 bit)"},
        {2, "Reserved"},
        {3, "Reserved"},
        {4, "Reserved"},
        {5, "Reserved"},
        {6, "Reserved"},
        {7, "Reserved"},
        {0, nullptr},
    },
};


const bool_field hf_add_ci = {
    "Add CI",
    0x08,
    "The MS should not add the letters for the Country's Initials to the text string",
    "The MS should add the letters for the Country's Initials and a separator (e.g. a "
    "space) to the text string",
};

const sms_field hf_text_string = {
    "Text String",
};

// 9.11.3.35	Network name
int mm::dissect_full_name_network(dissector d, context* ctx) {
    const use_context uc(ctx, "network-name", d, 0);

    const auto oct = d.tvb->uint8(d.offset);
    (void) d.add_item( &hf_extension);
    const auto code_scheme = (oct & 0x70u) >> 4u;
    (void) d.add_item( &hf_coding_scheme);
    (void) d.add_item( &hf_add_ci);

    //const auto num_spare_bits = oct & 0x07u;

    // (void) d.add_item(1, &hf_number_of_spare_bits);
    d.step(1);

    if (uc.length <= 1) return uc.length;

    if (code_scheme == 0) {
        (void) d.add_item(&hf_text_string, d.length);
        d.step(d.length);
        // 3GPP TS 23.038 7 bits        alphabet
    }
    if (code_scheme == 1) {
        (void) d.add_item(&hf_text_string, d.length);
        d.step(d.length);
    }
    if (code_scheme != 0 && code_scheme !=1 ) {
        diag("invalid code scheme %d\n", code_scheme);
    }

    return uc.length;
}
