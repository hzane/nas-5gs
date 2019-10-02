#include "../common/dissector.hh"
#include "../common/use_context.hh"


/* 8.2.18 Service reject */
int dissect_service_reject(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "service-reject", 3);
    // network to UE
    down_link(d.pinfo);

    /* 5GMM cause  9.11.3.2  M   V   1 */

    /*50  PDU session status 9.11.3.44    O    TLV    4 - 34*/

    /* 5F  T3346 value GPRS timer 2     9.11.2.4   O   TLV 3 */

    /* 78   EAP message 9.11.2.2    O    TLV-E    7-1503 */

    // XX	T3448 value	GPRS timer 3    9.11.2.4 O TLV 3

    return uc.length;
}
