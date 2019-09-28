#include <common/format.hh>

#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;


/*  8.2.11 DL NAS transport */
int mm::dissect_dl_nas_transparent(dissector d, context* ctx) {
    const use_context uc(ctx, "dl-nas-transport", d, 0);
    // network to UE
    down_link(d.packet);

    /* Initialize the private struct */
    // nas5gs_get_private_data(packet);

    /*Payload container type    Payload container type     9.11.3.40    M    V    1/2 H0*/
    d.add_item(1, "Payload container type", istring(d.uint8()&0x0fu));

    /*Spare half octet    Spare half octet    9.5    M    V    1/2 H1*/
    d.step(1);

    /* Payload container     9.11.3.39    M    LV-E    3-65537*/
    auto consumed = dissect_lv_e( &payload_container, d, ctx);
    d.step(consumed);

    /*12    PDU session ID    PDU session identity 2 9.11.3.41    C    TV    2 */
    // ELEM_OPT_TV( 0x12, , DE_NAS_5GS_MM_PDU_SES_ID_2, " - PDU session ID");
    consumed = dissect_opt_tv( &pdu_session_id, d, ctx);
    d.step(consumed);

    /*24    Additional information 9.11.2.1    O    TLV 3-n*/
    consumed = dissect_opt_tlv( &additional_information, d, ctx);
    d.step(consumed);

    /*58    5GMM cause  9.11.3.2    O    TV    2 */
     consumed = dissect_opt_tv( &nrmm_cause, d, ctx);
    d.step(consumed);

    /*37    Back-off timer value    GPRS timer 3 9.11.2.5    O    TLV    3 */
    // ELEM_OPT_TLV(0x37, , DE_GPRS_TIMER_3, " - Back-off timer value");
    consumed = dissect_opt_tlv( &backoff_gprs_timer3, d, ctx);
    d.step(consumed);

    return uc.length;
}


// Back-off timer value    GPRS timer 3 9.11.2.5
extern const element_meta mm::backoff_gprs_timer3 = {
    0x37,
    "GPRS timer 3 - Back-off timer",
    dissect_gprs_timer3_set,
    nullptr,
};
