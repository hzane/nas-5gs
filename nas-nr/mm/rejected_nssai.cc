#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

//  9.11.3.46    Rejected NSSAI
extern const element_meta mm::rejected_nssai = {
    0x11,
    "Rejected NSSAI",
    dissect_rejected_nssai,
    nullptr,
};


/* *   9.11.3.46    Rejected NSSAI page.389 */
int mm::dissect_rejected_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "rejected-nssai", d, 0);

    auto i = 1;
    while (d.length > 0) {
        const auto subtree = d.add_tree(2, formats("Rejected S-NSSAI %u", i++));
        use_tree   ut(d, subtree);

        const auto len = int(d.uint8() >> 4u);
        (void) d.add_item(1, &hf_reject_nssai_cause, enc::be);
        d.step(1);

        (void) d.add_item(1, &hf_slice_service_type, enc::be);
        d.step(1);
        if (len == 1) continue; // len == 1 || len == 4

        (void) d.add_item(3, &hf_slice_differentiator, enc::be);

        d.step(3);
    }
    return uc.length;
}

static const val_string ref_nssai_cause_values[] = {
    {0, "S-NSSAI not available in the current PLMN"},
    {1,
     "S-NSSAI not available in the current registration area All other values are "
     "reserved."},
    {0, nullptr},
};

const field_meta mm::hf_reject_nssai_cause = {
    "Cause",
    "nas.nr.mm.cause",
    ft::ft_uint8,
    fd::base_dec,
    ref_nssai_cause_values,
    nullptr,
    nullptr,
    0x0f,
};
