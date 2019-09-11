#include "../dissect_mm_msg.hh"

// 9.11.3.47 Request type page.390
int mm::dissect_request_type(dissector d, context* ctx) {
    const use_context uc(ctx, "request-type", d, -1);

    (void) d.add_item(1, &hf_request_type, enc::be);
    d.step(1);

    return 1;
}


// Request type  9.11.3.47
extern const element_meta mm::request_type = {
    0x80,
    "Request type",
    dissect_request_type,
    nullptr,
};

/*  9.11.3.47    Request type */
static const value_string nas_5gs_mm_req_type_vals[] = {
    {0x01, "Initial request"},
    {0x02, "Existing PDU session"},
    {0x03, "Initial emergency request"},
    {0x04, "Existing emergency PDU session"},
    {0x05, "Modification request"},
    {0x07, "Reserved"},
    {0, nullptr},
};



const field_meta mm::hf_request_type = {
    "Request type",
    "nas_5gs.mm.request.type",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_req_type_vals,
    nullptr,
    nullptr,
    0x0f,
};
