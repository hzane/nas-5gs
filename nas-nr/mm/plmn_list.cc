#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace nas;
using namespace mm;


const mccmnc_field hf_mccmnc = {
    "MCC / MNC",
};


/*  [3] 10.5.1.13 PLMN list GSM-A */
/*4A    Equivalent PLMNs    PLMN list     9.11.3.45    O    TLV    5-47*/
int mm::dissect_plmn_list(dissector d, context* ctx) {
    const use_context uc(ctx, "plmn-list", d, 0);

    // See subclause 10.5.1.13 in 3GPP TS 24.008 [12].
    auto num = 1;
    while (d.length >= 3) {
        const auto subtree = d.add_item(3, formats("PLMN[%u]", num++));
        use_tree ut(d, subtree);

        (void) d.add_item(&hf_mccmnc);

        d.step(3);
    }
    return d.offset - uc.offset;
}
