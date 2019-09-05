#include "../dissect_mm_msg.hh"

/* 9.11.3.10    ABBA */
int mm::dissect_abba(dissector d, context* ctx) {
    // indicate set of security features defined for 5GS as described in 3GPP TS 33.501
    // [24].
    const use_context uc(ctx, "abba", d, 0);

    d.add_item(d.length, &hf_abba, enc::be);
    d.step(d.length);

    return uc.length;
}

