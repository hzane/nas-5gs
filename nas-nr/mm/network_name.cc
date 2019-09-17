#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// See subclause 10.5.3.5a in 3GPP TS 24.008 [12].
extern const element_meta mm::full_name_network = {
    0x43,
    "Network name - Full Name",
    dissect_full_name_network,
    nullptr,

};

// See subclause 10.5.3.5a in 3GPP TS 24.008 [12].
extern const element_meta mm::short_name_network = {
    0x45,
    "Network Name - Short Name",
    dissect_short_name_network,
    nullptr,

};

// 9.11.3.35	Network name
int mm::dissect_short_name_network(dissector d, context* ctx) {
    return dissect_full_name_network(d, ctx);
}

// 9.11.3.35	Network name
int mm::dissect_full_name_network(dissector d, context* ctx) {
    const use_context uc(ctx, "network-name", d, 0);

    const auto oct = d.tvb->uint8(d.offset);
    (void) d.add_item(1, &hf_extension, enc::be);
    const auto code_scheme = (oct & 0x70u) >> 4u;
    (void) d.add_item(1, &hf_coding_scheme, enc::be);
    (void) d.add_item(1, &hf_add_ci, enc::be);

    //const auto num_spare_bits = oct & 0x07u;

    (void) d.add_item(1, &hf_number_of_spare_bits, enc::be);
    d.step(1);

    if (uc.length <= 1) return uc.length;

    if (code_scheme == 0) {
        (void) d.add_item(d.length, &hf_text_string, enc::none);
        d.step(d.length);
        // 3GPP TS 23.038 7 bits        alphabet
    }
    if (code_scheme == 1) {
        (void) d.add_item(d.length, &hf_text_string, enc::be);
        d.step(d.length);
    }
    if (code_scheme != 0 && code_scheme !=1 ) {
        diag("invalid code scheme %d\n", code_scheme);
    }

    return uc.length;
}

struct network_name_t {
    uint8_t extension;
    uint8_t code_scheme;
    uint8_t add_ci;
    string  text;
};
