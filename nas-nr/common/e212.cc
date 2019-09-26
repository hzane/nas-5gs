#include "definitions.hh"
#include "dissector.hh"

/* *   8   7   6   5   4   3   2   1
 * +---+---+---+---+---+---+---+---+
 * |  MCC digit 2  |  MCC digit 1  |  octet x
 * +---------------+---------------+
 * |  MNC digit 3  |  MCC digit 3  |  octet x+1
 * +---------------+---------------+
 * |  MNC digit 2  |  MNC digit 1  |  octet x+2
 * +---------------+---------------+
 *
 */
int dissect_mcc_mnc(dissector d, context*ctx, mcc_mnc_t*ret) {
    uint16_t a    = d.uint8();
    uint16_t b     = d.uint8();
    uint16_t c     = d.uint8();

    ret->mcc       = (a & 0x0fu) * 100 + ((a & 0xf0u) >> 4u) * 10 + (b & 0x0fu);


    /* MNC, Mobile network code (octet 3 bits 5 to 8, octet 4)  */
    const auto mnc3 = b >> 4u;
    const auto mnc1 = c & 0x0fu;
    const auto mnc2 = c >> 4u;

    ret->mnc  = 100 * mnc1 + 10 * mnc2 + mnc3;

    return 3;
}
