#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 9.11.3.10    ABBA */
// 3GPP TS 33.501
result_t dissect_abba(dissector d, context* ctx, abba_t* ret) {
    // indicate set of security features defined for 5GS as described in 3GPP TS 33.501
    // [24].
    return de_octet(d, ctx, ret).step(d);

    /*NOTE 1:	If the UE receives the ABBA IE with a length that is set to a value of 2
     *and with a value of 0000H, the UE shall use the length and the contents of
     *the ABBA IE as received from the network.
     *NOTE 2:	If the UE receives the ABBA IE with a length that is
     *set to a value larger than 2 or with a value that is different from 0000H,
     *the UE shall use the length and the contents of the ABBA IE as received from the network.
     */
}
