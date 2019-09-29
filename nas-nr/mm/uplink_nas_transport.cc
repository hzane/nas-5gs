#include "../common/formats.hh"

#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

/* 8.2.10    UL NAS transport */
int mm::dissect_ul_nas_transport(dissector d, context* ctx) {
    const use_context uc(ctx, "ul-nas-transport", d, 1);

    /* Direction: UE to network */
    up_link(d.packet);

    /* Initialize the private struct */
    // nas5gs_get_private_data(packet);

    /* Payload container type   9.11.3.40    M    V    1/2 */
    d.add_item(1, "Payload container type", istring(d.uint8()));

    /*Spare half octet  9.5    M    V    1/2*/
    d.step(1);

    /* Payload container  9.11.3.39    M    LV-E    3-65537*/
    auto consumed = dissect_lv_e( &payload_container, d, ctx);
    d.step(consumed);

    /*12 PDU session ID 2 9.11.3.41    C    TV    2 */
    consumed = dissect_opt_tv( &pdu_session_id, d, ctx);
    d.step(consumed);

    /*59    Old PDU session ID    PDU session identity 2 9.11.3.41    O    TV    2 */
     consumed = dissect_opt_tv( &old_pdu_session_id, d, ctx);
    d.step(consumed);

    /*8-    Request type  9.11.3.47    O    TV    1 */
     consumed = dissect_opt_tv_short( &request_type, d, ctx);
    d.step(consumed);

    /*22    S-NSSAI   9.11.2.8    O    TLV    3-10 */
    consumed = dissect_opt_tlv( &s_nssai, d, ctx);
    d.step(consumed);

    /*25    DNN 9.11.2.1A    O    TLV    3-102 */
    consumed = dissect_opt_tlv( &dnn, d, ctx);
    d.step(consumed);

    /*24 Additional information  9.11.2.1    O    TLV 3-n */
    consumed = dissect_opt_tlv( &additional_information, d, ctx);
    d.step(consumed);

    // Z	MA PDU session information	MA PDU session information	O	TV	1


    return uc.length;
}
