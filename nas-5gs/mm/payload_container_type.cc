#include "../dissect_mm_msg.hh"

// int dissect_pld_cont_type(dissector d, context* ctx = nullptr);

// Payload container type   9.11.3.40
const element_meta mm::pld_cont_type = {
    0x80,
    "Payload container type",
    mm::dissect_pld_cont_type,
    nullptr,
};


// Payload container type   9.11.3.40
int mm::dissect_pld_cont_type(dissector d, context* ctx) {
    const auto oct = d.tvb->uint8(d.offset) & 0x0fu;
    store_payload_content_type(ctx, oct);

    d.add_item(1, &mm::hf_pld_cont_type, enc::be);
    return 1;
}
// Payload container type   9.11.3.40


