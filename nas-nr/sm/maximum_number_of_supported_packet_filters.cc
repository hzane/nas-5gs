#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace sm;

const field_meta hf_max_supported_packet_filters = {
    "Maximum number of supported packet filters",
    "nas.nr.max_n_supported_filters",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_max_supported_packet_filters_c = {
    "Maximum number of supported packet filters(continued)",
    "nas.nr.max_n_supported_filters",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0xe0u,
};

//  9.11.4.9    Maximum number of supported packet filters
int sm::dissect_max_number_supported_packet_filter(dissector d, context* ctx) {
    const use_context uc(ctx, "max-nof-supported-packet-filters", d, -1);

    (void) d.add_item(1, &hf_max_supported_packet_filters);
    d.step(1);
    (void) d.add_item(1, &hf_max_supported_packet_filters_c);
    d.step(1);

    return 2;
}

struct supported_packet_filter_max_number_t {
    uint8_t max;
    uint8_t max_c;
};

// Maximum number of supported packet filter 9.11.4.9
const element_meta sm::max_supported_packet_filters = {
    0x55,
    "Maximum number of supported packet filter",
    dissect_max_number_supported_packet_filter,
    nullptr,
};
