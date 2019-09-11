#include "../dissect_mm_msg.hh"

// Payload container type   9.11.3.40
const element_meta mm::payload_container_type = {
    0x80,
    "Payload container type",
    mm::dissect_payload_container_type,
    nullptr,
};


// Payload container type   9.11.3.40
int mm::dissect_payload_container_type(dissector d, context* ctx) {
    const use_context uc(ctx, "payload-container-type", d, -1);

    const uint8_t oct = d.tvb->uint8(d.offset) & 0x0fu;
    store_payload_content_type(ctx, oct);

    auto i = d.add_item(1, &mm::hf_payload_container_type, enc::be);
    unused(i);
    return 1;
}


/*  9.11.3.40    Payload container type */
extern const value_string mm::mm_pld_cont_type_values[] = {
    {0x01, "N1 SM information"},
    {0x02, "SMS"},
    {0x03, "LTE Positioning Protocol (LPP) message container"},
    {0x04, "SOR transparent container"},
    {0x05, "UE policy container"},
    {0x06, "UE parameters update transparent container"},
    {0x0f, "Multiple payloads"},
    {0, nullptr},
};

/*  9.11.3.40    Payload container type */
extern const field_meta mm::hf_payload_container_type = {
    "Payload container type",
    "nas_5gs.mm.payload.type",
    ft::ft_uint8,
    fd::base_dec,
    mm_pld_cont_type_values,
    nullptr,
    nullptr,
    0x0f,
};

