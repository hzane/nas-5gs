#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// LADN information   9.11.3.30
const element_meta mm::ladn_information = {
    0x79,
    "LADN information",
    dissect_ladn_information,
    nullptr,
};


/* 9.11.3.30    LADN information  */
int mm::dissect_ladn_information(dissector d, context* ctx) {
    const use_context uc(ctx, "ladn-information", d, 0);
    
    NASNR_AUTO(int)       i   = 1;
    while (d.length > 0) {
        const NASNR_AUTO(int) start = d.offset;
        NASNR_AUTO(proto_node*)       subtree = d.add_item(2, "LADN %u", i++);
        use_tree ut(d, subtree);
        
        /* DNN value (octet 5 to octet m):
         * LADN DNN value is coded as the length and value part of DNN information element
         * as specified in subclause 9.11.2.1A starting with the second octet
         */
        NASNR_AUTO(int) length = static_cast< int >(d.tvb->uint8(d.offset));
        // NASNR_AUTO(proto_node*) n = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        /* 5GS tracking area identity list (octet m+1 to octet a):
         * 5GS tracking area identity list field is coded as the length and the value part
         * of the 5GS Tracking area identity list information element as specified in
         * subclause 9.11.3.9 starting with the second octet
         */
        NASNR_AUTO(int) consumed = dissect_dnn(d.slice(length), ctx);
        d.step(consumed);

        // (void) d.add_item(1, &hf_mm_length, enc::be);
        length   = d.uint8();
        d.step(1);

        consumed = dissect_tracking_area_id_list(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(d.offset - start);
        
    }

    return uc.length;
}
