#include "../dissect_sm_msg.hh"

using namespace nas;
using namespace sm;


const field_meta hf_max_supported_packet_filters = {
    "Maximum number of supported packet filters",
    "nas_5gs.max_n_supported_filters",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0,
};
const field_meta hf_max_supported_packet_filters_c = {
    "Maximum number of supported packet filters(continued)",
    "nas_5gs.max_n_supported_filters",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0xe0u,
};

//  9.11.4.9    Maximum number of supported packet filters
int sm::dissect_max_num_sup_kpt_flt(dissector d, context* ctx) {
    d.add_item(1, &hf_max_supported_packet_filters, enc::be);
    d.step(1);
    d.add_item(1, &hf_max_supported_packet_filters_c, enc::be);
    d.step(1);

    return 2;
}
