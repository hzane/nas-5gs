#include "../dissect_mm_msg.hh"


// 9.11.3.58	Non-3GPP NW provided policies
int mm::dissect_n3gpp_nw_provided_policies(dissector d, context* ctx) {
    const use_context uc(ctx, "non-3gpp-nw-provided-policies", d, -1);

    // See subclause 10.5.5.37 in 3GPP TS 24.008
    d.add_item(1, &hf_gsm_a_n3en_ind, enc::be);

    /* no length check possible */
    return 1;
}
