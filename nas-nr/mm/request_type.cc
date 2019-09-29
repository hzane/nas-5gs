#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

/* *     9.11.3.47    Request type */
const tag_field hf_request_type = {
    "Request type",
    0x0f,
    (const v_string[]){
        {0x01, "Initial request"},
        {0x02, "Existing PDU session"},
        {0x03, "Initial emergency request"},
        {0x04, "Existing emergency PDU session"},
        {0x05, "Modification request"},
        {0x07, "Reserved"},
        {0, nullptr},
    },
};

// 9.11.3.47 Request type page.390
int mm::dissect_request_type(dissector d, context* ctx) {
    const use_context uc(ctx, "request-type", d, -1);

    (void) d.add_item( &hf_request_type);
    d.step(1);

    return 1;
}
