#include "../dissect_sm_msg.hh"
#include "../packet_info.hh"
#include "../ber.hh"

using namespace cmn;
using namespace nas;
using namespace sm;

/* 8.3.1 PDU session establishment request */
int sm::dissect_pdu_ses_establishment_req(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-establishment-request", d, 0);

    /* Direction: UE to network*/
    up_link(d.pinfo);

    /* Integrity protection maximum data rate   9.11.4.7    M    V    2 */
    auto consumed = dissect_v(nullptr, &int_prot_max_data_rate, d, ctx);
    d.step(consumed);

    /*9- PDU session type 9.11.4.11    O    TV    1*/
    consumed = dissect_opt_tv_short(nullptr, &pdu_ses_type, d, ctx);
    d.step(consumed);

    /*A- SSC mode 9.11.4.16    O    TV    1*/
    consumed = dissect_opt_tv_short(nullptr, &ssc_mode, d, ctx);
    d.step(consumed);

    /*28	5GSM capability	9.11.4.1	O	TLV	3-15 */
    consumed = dissect_opt_tlv(nullptr, &sm_cap, d, ctx);
    d.step(consumed);

    /*55	Maximum number of supported packet filters 9.11.4.9	O	TV	3 */
    consumed = dissect_opt_tv(nullptr, &max_of_supported_pkt_filter, d, ctx);
    d.step(consumed);

    /*B-	Always-on PDU session requested	 9.11.4.4	O	TV	1*/
    consumed = dissect_opt_tv_short(nullptr, &alwayson_pdu_session_req, d, ctx);
    d.step(consumed);

    /*39	SM PDU DN request container	 9.11.4.15	O	TLV	3-255*/
    consumed = dissect_opt_tlv(nullptr, &sm_pdu_dn_req_cont, d, ctx);
    d.step(consumed);

    /*7B	Extended protocol configuration options 9.11.4.6	O	TLV-E	4-65538*/
    consumed = dissect_opt_tlv_e(nullptr, &ext_pco, d, ctx);
    d.step(consumed);

    return uc.length;
}
