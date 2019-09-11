#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

/* 9.11.3.50    Service type page.396 */
int mm::dissect_service_type(dissector d, context* ctx) {
    const use_context uc(ctx, "service-type", d, -1);

    (void) d.add_item(1, &hfm_mm_serv_type, enc::be);
    d.step(1);

    return 1;
}

// Service type 9.11.3.50
const element_meta mm::service_type = {
    0xff,
    "Service type",
    dissect_service_type,
    nullptr,
};

/* *     9.11.3.50    Service type page.396 */
/* Used inline as H1 (Upper nibble)*/
const val_string mm::mm_serv_type_vals[] = {
    {0x00, "Signalling"},
    {0x01, "Data"},
    {0x02, "Mobile terminated services"},
    {0x03, "Emergency services"},
    {0x04, "Emergency services fallback"},
    {0x05, "High priority access"},
    {0x06, "elevated signalling"},
    {0x07, R"(unused; shall be interpreted as "signalling", if received by the network)"},
    {0x08, "unused; shall be interpreted as \"signalling\", if received by the network"},
    {0x09, "unused; shall be interpreted as \"data\", if received by the network"},
    {0x0a, "unused; shall be interpreted as \"data\", if received by the network"},
    {0x0b, "unused; shall be interpreted as \"data\", if received by the network"},
    {0, nullptr},
};
const field_meta mm::hfm_mm_serv_type = {
    "Service type",
    "nas_5gs.mm.service.type",
    ft::ft_uint8,
    fd::base_dec,
    mm_serv_type_vals,
    nullptr,
    nullptr,
    0xF0,
};
