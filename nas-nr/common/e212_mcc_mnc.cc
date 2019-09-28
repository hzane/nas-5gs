#include "common.hh"
#include "config.hh"
#include "field_meta.hh"
#include "format.hh"


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

    d.add_item(3, "MCC", mcc_string(d.ptr()));
    d.add_item(3, "MNC", mnc_string(d.ptr()));
    return 3;
}


