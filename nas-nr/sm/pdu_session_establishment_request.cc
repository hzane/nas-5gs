#include "../common/ber.hh"
#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"
#include "common/packet.hh"


using namespace nas;
using namespace sm;

/* 8.3.1 PDU session establishment request */
int sm::dissect_pdu_session_establishment_request(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-establishment-request", d, 0);

    /* Direction: UE to network*/
    up_link(d.packet);

    /* Integrity protection maximum data rate   9.11.4.7    M    V    2 */
    auto consumed = dissect_v( &integrity_protection_max_data_rate, d, ctx);
    d.step(consumed);

    /*9- PDU session type 9.11.4.11    O    TV    1*/
    consumed = dissect_opt_tv_short( &pdu_session_type, d, ctx);
    d.step(consumed);

    /*A- SSC mode 9.11.4.16    O    TV    1*/
    consumed = dissect_opt_tv_short( &ssc_mode, d, ctx);
    d.step(consumed);

    /*28	5GSM capability	9.11.4.1	O	TLV	3-15 */
    consumed = dissect_opt_tlv( &nrsm_capability, d, ctx);
    d.step(consumed);

    /*55	Maximum number of supported packet filters 9.11.4.9	O	TV	3 */
    consumed = dissect_opt_tv( &max_supported_packet_filters, d, ctx);
    d.step(consumed);

    /*B-	Always-on PDU session requested	 9.11.4.4	O	TV	1*/
    consumed = dissect_opt_tv_short( &alwayson_pdu_session_requested, d, ctx);
    d.step(consumed);

    /*39	SM PDU DN request container	 9.11.4.15	O	TLV	3-255*/
    consumed = dissect_opt_tlv( &sm_pdu_dn_request_container, d, ctx);
    d.step(consumed);

    /*7B	Extended protocol configuration options 9.11.4.6	O	TLV-E	4-65538*/
    consumed = dissect_opt_tlv_e( &extended_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
