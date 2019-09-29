#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

/* [14] 10.5.5.37 Non-3GPP NW provided policies */
static const tf_string tfind = {
    "Use of non-3GPP emergency numbers permitted",
    "Use of non-3GPP emergency numbers not permitted",
};

const bool_field hf_n3en_indicator = {
    "N3EN indicator",
    0x01,
    tfind.false_string,
    tfind.true_string,
};

// 9.11.3.58	Non-3GPP NW provided policies
int mm::dissect_n3gpp_nw_provided_policies(dissector d, context* ctx) {
    const use_context uc(ctx, "non-3gpp-nw-provided-policies", d, -1);

    // See subclause 10.5.5.37 in 3GPP TS 24.008
    (void) d.add_item(&hf_n3en_indicator);

    /* no length check possible */
    return 1;
}
