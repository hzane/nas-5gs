#include "definitions.hh"
#include "dissector.hh"
#include "ies.hh"

result_t die_mcc_mnc(dissector d, context* ctx, mcc_mnc_t* ret) {
    const use_context uc(&d, ctx, "mcc-mnc", 0);
    auto              a = d.uint8(true), b = d.uint8(true), c = d.uint8(true);

    ret->mcc = (a & 0x0fu) * 100 + ((a & 0xf0u) >> 4u) * 10 + (b & 0x0fu);

    /* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4)  */
    const auto mnc3 = b >> 4u;
    const auto mnc1 = c & 0x0fu;
    const auto mnc2 = c >> 4u;

    ret->mnc = 10 * mnc1 + mnc2;
    if (mnc3 != 0xf) ret->mnc = ret->mnc * 10 + mnc3;

    return {uc.consumed()};
}
