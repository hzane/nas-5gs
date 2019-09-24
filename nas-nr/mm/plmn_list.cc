#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

const element_meta mm::plmn_list = {
    0x4a,
    "Equivalent PLMNs",
    dissect_plmn_list,
    nullptr,
};

/*  [3] 10.5.1.13 PLMN list GSM-A */
/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
int mm::dissect_plmn_list(dissector d, context* ctx) {
    const use_context uc(ctx, "plmn-list", d, 0);
    
    // See subclause 10.5.1.13 in 3GPP TS 24.008 [12].
    auto num = 1;
    while (d.length >= 3) {
        const auto subtree = d.add_tree(3, formats("PLMN[%u]", num++));
        use_tree ut(d, subtree);

        (void) d.add_item(3, &hf_mobile_country_code, enc::na);
        (void) d.add_item(3, &hf_mobile_network_code, enc::na);

        d.step(3);
    }
    return d.offset - uc.offset;
}
