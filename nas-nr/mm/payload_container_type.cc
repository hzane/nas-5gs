#include <common/format.hh>

#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

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

    d.set_item(1, vstring(payload_container_type_values, d.uint8()&0x0fu));

    return 1;
}


/*  9.11.3.40    Payload container type */
extern const value_string mm::payload_container_type_values[] = {
    {0x01, "N1 SM information"},
    {0x02, "SMS"},
    {0x03, "LTE Positioning Protocol (LPP) message container"},
    {0x04, "SOR transparent container"},
    {0x05, "UE policy container"},
    {0x06, "UE parameters update transparent container"},
    {0x0f, "Multiple payloads"},
    {0, nullptr},
};
