#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace mm;


/* 9.11.3.10    ABBA */
int mm::dissect_abba_set(dissector d, context* ctx) {
    // indicate set of security features defined for 5GS as described in 3GPP TS 33.501
    // [24].
    const use_context uc(ctx, "abba", d, 0);

    d.tree->set_item(d.length, &hf_abba, enc::be);
    d.step(d.length);
    
    return uc.length;
    /*NOTE 1:	If the UE receives the ABBA IE with a length that is set to a value of 2
     *and with a value of 0000H, the UE shall use the length and the contents of
     *the ABBA IE as received from the network.
     *NOTE 2:	If the UE receives the ABBA IE with a length that is
     *set to a value larger than 2 or with a value that is different from 0000H,
     *the UE shall use the length and the contents of the ABBA IE as received from the network.
     */
}

extern const element_meta mm::abba = {
    0x38,
    "ABBA",
    dissect_abba_set,
    nullptr,
};

const field_meta mm::hf_abba = {
    "ABBA Contents",
    "nas_5gs.mm.abba.contents",
    ft::ft_bytes,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
