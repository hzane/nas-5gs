#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 3GPP TS 23.040 version 6.6.0 Release 6
9.2.3.11 TP-Service-Centre-Time-Stamp (TP-SCTS)
 * 10.5.3.8 Time Zone  in 3GPP TS 24.008 [12]*/
int dissect_timezone_set(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "local-time-zone", -1);

    /* no length check possible */
    return 1;
}
