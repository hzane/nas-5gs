#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// 9.11.3.58	Non-3GPP NW provided policies
int mm::dissect_n3gpp_nw_provided_policies(dissector d, context* ctx) {
    const use_context uc(ctx, "non-3gpp-nw-provided-policies", d, -1);

    // See subclause 10.5.5.37 in 3GPP TS 24.008
    (void) d.add_item(1, &hf_n3en_indicator, enc::be);

    /* no length check possible */
    return 1;
}

// Non-3GPP NW policies Non-3GPP NW provided policies 9.11.3.58
const element_meta mm::n3gpp_nw_provided_policies = {
    0xd0,
    "Non-3GPP NW provided policies",
    dissect_n3gpp_nw_provided_policies,
    nullptr,
};

struct n3gpp_network_provided_policies_t {
    uint8_t _;
};
