#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// Configured NSSAI    NSSAI 9.11.3.37
extern const element_meta mm::configured_nssai = {
    0x31,
    "Configured NSSAI",
    dissect_configured_nssai,
    nullptr,
};

/* 9.11.3.37    NSSAI */
int mm::dissect_configured_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "configured-nssai", d, 0);

    /*S-NSSAI value is coded as the length and value part of S-NSSAI information element
     * as specified in subclause 9.11.2.8 starting with the second octet.*/

    NASNR_AUTO(int) i = 1;
    while (d.length > 0) {
        NASNR_AUTO(proto_node*) const subtree = d.add_item(2, "S-NSSAI %u", i++);
        use_tree   ut(d, subtree);

        NASNR_AUTO(int) const length = static_cast< int >(d.tvb->uint8(d.offset));
        // NASNR_AUTO(proto_node*) n = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        NASNR_AUTO(int) const consumed = cmn::dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);
        
    }
    return uc.length;
}



/* 9.11.3.37    NSSAI
 * S-NSSAI value is coded as the length and value part of S-NSSAI information element
as specified in subclause 9.11.2.8 starting with the second octet.
 */
int mm::dissect_allowed_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "allowed-nssai", d, 0);

    NASNR_AUTO(int) i = 1;
    while (d.length > 0) {
        NASNR_AUTO(proto_node*) const subtree = d.add_item(-1, "S-NSSAI %u", i++);
        use_tree   ut(d, subtree);

        NASNR_AUTO(uint8_t) const l    = d.uint8();
        // NASNR_AUTO(proto_node*)       item = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        const NASNR_AUTO(int) consumed = dissect_s_nssai(d.slice(l), ctx);
        d.step(consumed);
        d.tree->set_length(consumed + 1);
        
    }
    return uc.length;
}

/* 9.11.3.37    NSSAI*/
int mm::dissect_requested_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "requested-nssai", d, 0);

    NASNR_AUTO(int) i = 1;
    while (d.length > 0) {
        NASNR_AUTO(proto_node*)     subtree = d.add_item(2, "S-NSSAI %u", i++);
        use_tree ut(d, subtree);

        NASNR_AUTO(int) const length = static_cast< int >(d.tvb->uint8(d.offset));
        // NASNR_AUTO(proto_node*) n = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        // 9.11.2.8
        NASNR_AUTO(int) const consumed = dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
        
    }
    return uc.length;
}

