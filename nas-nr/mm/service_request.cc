#include "../common/dissector.hh"
#include "../common/use_context.hh"

/* 8.2.16 Service request page.317 */
int dissect_service_request(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "service-request", 0);
    // UE to network
    up_link(d.pinfo);

    /* ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2 */

    // Service type 9.11.3.50 M V 1 / 2

    /* 5G-S-TMSI    5GS mobile identity 9.11.3.4    M    LV    9 */

    /*40 Uplink data status  9.11.3.57   O   TLV  4 - 34*/

    /*50 PDU session status  9.11.3.44  O  TLV   4 - 34*/

    /*25 Allowed PDU session status  9.11.3.13  O    TLV    4 - 34*/

    /* 71  NAS message container 9.11.3.33    O    TLV-E    4-n */

    return uc.length;
}
