#include "../dissect_mm_msg.hh"

using namespace cmn;

//  9.11.3.46    Rejected NSSAI
extern const element_meta mm::rej_nssai = {
    0x11,
    "Rejected NSSAI",
    dissect_rejected_nssai,
    nullptr,
};

// Configured NSSAI    NSSAI 9.11.3.37
extern const element_meta mm::configured_nssai = {
    0x31,
    "Configured NSSAI",
    dissect_configured_nssai,
    nullptr,
};


const val_string ref_nssai_cause_values[] = {
    {0, "S-NSSAI not available in the current PLMN"},
    {1,
     "S-NSSAI not available in the current registration area All other values are "
     "reserved."},
    {0, nullptr},
};
const field_meta hf_rej_nssai_cause = {
    "Cause",
    "nas_5gs.mm.cause",
    ft::ft_uint8,
    fd::base_dec,
    ref_nssai_cause_values,
    nullptr,
    nullptr,
    0x0f,
};

/* *   9.11.3.46    Rejected NSSAI page.389 */
int mm::dissect_rejected_nssai(dissector d, context* ctx) {
    const use_context uc(ctx, "rejected-nssai", d, 0);

    auto i = 1;
    while (d.length > 0) {
        const auto subtree = d.add_item(2, "Rejected S-NSSAI %u", i++);
        use_tree   ut(d, subtree);

        const auto len = int(d.uint8() >> 4u);
        auto n = d.add_item(1, &hf_rej_nssai_cause, enc::be);
        d.step(1);

        n = d.add_item(1, &hf_sst, enc::be);
        d.step(1);
        if (len == 1) continue; // len == 1 || len == 4

        n = d.add_item(3, &hf_sd, enc::be);

        unused(n);
        d.step(3);
    }
    return uc.length;
}

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



/*
 * 9.11.3.37    NSSAI
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

