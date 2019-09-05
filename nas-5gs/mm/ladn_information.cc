#include "../dissect_mm_msg.hh"

using namespace cmn;

// LADN information   9.11.3.30
const element_meta mm::ladn_inf = {
    0x79,
    "LADN information",
    dissect_ladn_inf,
    nullptr,
};


/* 9.11.3.30    LADN information  */
int mm::dissect_ladn_inf(dissector d, context* ctx) {
    const auto len = d.length;
    auto       i   = 1;
    while (d.length > 0) {
        const auto start = d.offset;
        auto subtree     = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "LADN %u", i);
        d.tree           = subtree;
        /* DNN value (octet 5 to octet m):
         * LADN DNN value is coded as the length and value part of DNN information element
         * as specified in subclause 9.11.2.1A starting with the second octet
         */
        auto length = static_cast< int >(d.tvb->uint8(d.offset));
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        /* 5GS tracking area identity list (octet m+1 to octet a):
         * 5GS tracking area identity list field is coded as the length and the value part
         * of the 5GS Tracking area identity list information element as specified in
         * subclause 9.11.3.9 starting with the second octet
         */
        auto consumed = dissect_dnn(d.slice(length), ctx);
        d.step(consumed);

        d.add_item(1, &hf_mm_length, enc::be);
        d.step(consumed);

        length   = d.tvb->uint8(d.offset);
        consumed = dissect_ta_id_list(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(d.offset - start);

        ++i;
    }
    return len;
}
