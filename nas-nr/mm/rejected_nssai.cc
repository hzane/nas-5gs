#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

const tag_field hf_reject_nssai_cause = {
    "Cause",
    0x0f,
    (const v_string[]){
        {0, "S-NSSAI not available in the current PLMN"},
        {1,
            "S-NSSAI not available in the current registration area All other values are "
            "reserved."},
        {0, nullptr},
    },
};

extern const uint8_field hf_slice_service_type;
extern const uint24_field hf_slice_differentiator;

/* *   9.11.3.46    Rejected NSSAI page.389 */
int mm::dissect_rejected_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "rejected-nssai", d, 0);

    auto i = 1;
    while (d.length > 0) {
        const auto subtree = d.add_item(2, formats("Rejected S-NSSAI %u", i++));
        use_tree   ut(d, subtree);

        const auto len = int(d.uint8() >> 4u);
        (void) d.add_item(&hf_reject_nssai_cause);
        d.step(1);

        (void) d.add_item( &hf_slice_service_type);
        d.step(1);
        if (len == 1) continue; // len == 1 || len == 4

        (void) d.add_item( &hf_slice_differentiator);

        d.step(3);
    }
    return uc.length;
}



