#include "../base/common.hh"
#include "../base/config.hh"
#include "../base/field_meta.hh"

using mcc = string;
using mnc = string;

namespace cmn {
extern const field_meta   hf_e212_mcc;
extern const field_meta   hf_e212_mnc;
}


/*
 * MCC/MNC dissection - little endian MNC encoding
 *
 * MNC of length 2:
 *
 *   8   7   6   5   4   3   2   1
 * +---+---+---+---+---+---+---+---+
 * |  MCC digit 2  |  MCC digit 1  |  octet x
 * +---------------+---------------+
 * |    Filler     |  MCC digit 3  |  octet x+1
 * +---------------+---------------+
 * |  MNC digit 2  |  MNC digit 1  |  octet x+2
 * +---------------+---------------+
 *
 * MNC of length 3:
 *
 *   8   7   6   5   4   3   2   1
 * +---+---+---+---+---+---+---+---+
 * |  MCC digit 2  |  MCC digit 1  |  octet x
 * +---------------+---------------+
 * |  MNC digit 3  |  MCC digit 3  |  octet x+1
 * +---------------+---------------+
 * |  MNC digit 2  |  MNC digit 1  |  octet x+2
 * +---------------+---------------+
 *
 */

/*
 * Return MCC MNC in a packet scope allocated string that can be used in labels.
 * Little Endian encoded
 */
int cmn::dissect_e212_mcc_mnc(dissector d, context*) {

    (void) d.add_item(3, &hf_e212_mcc, enc::be); // mcc
    (void) d.add_item(3, &hf_e212_mnc, enc::be); // mnc

    return 3;
}


const field_meta cmn::hf_e212_mcc = {
    "MCC",
    "mcc",
    ft::ft_bytes,
    fd::mcc,
    nullptr,
    nullptr,
    nullptr,
    0,
};

const field_meta cmn::hf_e212_mnc = {
    "MNC",
    "nas.nr.cmn.mnc",
    ft::ft_bytes,
    fd::mnc,
    nullptr,
    nullptr,
    nullptr,
    0,
};
