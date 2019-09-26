#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 3GPP TS 23.040 version 6.6.0 Release 6
 * 10.5.3.8 Time Zone  in 3GPP TS 24.008 [12]*/
int dissect_timezone_set(dissector d, context* ctx) {
    const use_context uc(ctx, "local-time-zone", d, -1);

    /* 3GPP TS 23.040 version 6.6.0 Release 6
     * 9.2.3.11 TP-Service-Centre-Time-Stamp (TP-SCTS)
     * :
     * The Time Zone indicates the difference, expressed in quarters of an hour,
     * between the local time and GMT. In the first of the two semi-octets,
     * the first bit (bit 3 of the seventh octet of the TP-Service-Centre-Time-Stamp
     * field) represents the algebraic sign of this difference (0: positive, 1: negative).
     */

    /* no length check possible */
    return 1;
}
