#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// Emergency number list  9.11.3.23
int mm::dissect_emerg_num_list(dissector d, context* ctx) {
    const use_context uc(ctx, "emergency-number-list", d, 0);

    // See subclause 10.5.3.13 in 3GPP TS 24.008 [12].
    static const field_meta* flags[] = {
        &hf_gsma_svc_cat_b0,
        &hf_gsma_svc_cat_b1,
        &hf_gsma_svc_cat_b2,
        &hf_gsma_svc_cat_b3,
        &hf_gsma_svc_cat_b4,
        nullptr,
    };
    const auto len = d.length;

    while (d.length > 0) {
        /* Length of 1st Emergency Number information note 1) octet 3
         * NOTE 1: The length contains the number of octets used to encode the
         * Emergency Service Category Value and the Number digits.
         */
        auto       elen    = d.uint8();
        const auto subtree = d.add_item(elen + 1, &hf_gsma_eni, enc::be);
        use_tree   ut(d, subtree);

        (void) d.add_item(1, &hf_gsma_eni_length, enc::be);
        d.step(1);

        /* 0 0 0 Emergency Service Category Value 
         * Table 10.5.135d/3GPP TS 24.008: Service Category information element
         */
        d.add_bits(flags);
        d.step(1);
        --elen;
        (void) d.add_item(elen, &hf_gsma_emergency_bcd_num, enc::be);

        d.step(elen);        
    }
    return len;
}



const element_meta mm::emerg_num_list = {
    0x34,
    "Emergency number list",
    dissect_emerg_num_list,
    nullptr,
};


