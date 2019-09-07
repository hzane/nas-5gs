#include "../dissect_mm_msg.hh"

using namespace cmn;


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

    auto i = 1;
    while (d.length > 0) {
        const auto subtree = d.add_item(2, "S-NSSAI %u", i++);
        use_tree   ut(d, subtree);

        const int length = static_cast< int >(d.tvb->uint8(d.offset));
        auto n = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        const auto consumed = cmn::dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);

        unused(n);
    }
    return uc.length;
}



/* 9.11.3.37    NSSAI
 * S-NSSAI value is coded as the length and value part of S-NSSAI information element
as specified in subclause 9.11.2.8 starting with the second octet.
 */
int mm::dissect_allowed_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "allowed-nssai", d, 0);

    auto i = 1;
    while (d.length > 0) {
        const auto subtree = d.add_item(-1, "S-NSSAI %u", i++);
        use_tree   ut(d, subtree);

        const auto l    = d.uint8();
        auto       item = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        const auto consumed = dissect_s_nssai(d.slice(l), ctx);
        d.step(consumed);
        d.tree->set_length(consumed + 1);

        unused(item);
    }
    return uc.length;
}

/* 9.11.3.37    NSSAI*/
int mm::dissect_requested_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "requested-nssai", d, 0);

    auto i = 1;
    while (d.length > 0) {
        auto     subtree = d.add_item(2, "S-NSSAI %u", i++);
        use_tree ut(d, subtree);

        const auto length = static_cast< int >(d.tvb->uint8(d.offset));
        auto n = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        // 9.11.2.8
        const auto consumed = dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);

        unused(n);
    }
    return uc.length;
}

