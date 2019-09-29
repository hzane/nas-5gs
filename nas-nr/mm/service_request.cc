#include "../common/ber.hh"
#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace nas;
using namespace mm;

static const psi_field ul_data_psi_1= {
    "PSI",
    0xfeu,
    0,
    "no uplink data are pending",
    "uplink data are pending",
};
static const psi_field ul_data_psi_8= {
    "PSI",
    0xffu,
    8,
    "no uplink data are pending",
    "uplink data are pending",
};

/* 8.2.16 Service request page.317 */
int mm::dissect_service_request(dissector d, context* ctx) {
    const use_context uc(ctx, "service-request", d, 0);
    // UE to network
    up_link(d.packet);

    /* ngKSI     NAS key set identifier 9.11.3.32    M    V    1/2 */
    dissect_v( &nas_ksi, d, ctx);

    // Service type 9.11.3.50 M V 1 / 2
    (void) dissect_service_type(d, ctx);
    d.step(1);

    /* 5G-S-TMSI    5GS mobile identity 9.11.3.4    M    LV    9 */
    auto consumed = dissect_lv_e( &s_tmsi, d, ctx);
    d.step(consumed);

    /*40 Uplink data status  9.11.3.57   O   TLV  4 - 34*/
    consumed = dissect_opt_tlv( &uplink_data_status, d, ctx);
    d.step(consumed);

    /*50 PDU session status  9.11.3.44  O  TLV   4 - 34*/
    consumed = dissect_opt_tlv( &pdu_session_status, d, ctx);
    d.step(consumed);

    /*25 Allowed PDU session status  9.11.3.13  O    TLV    4 - 34*/
    consumed = dissect_opt_tlv( &allowed_pdu_session_status, d, ctx);
    d.step(consumed);

    /* 71  NAS message container 9.11.3.33    O    TLV-E    4-n */
    consumed = dissect_opt_tlv_e( &nas_msg_container, d, ctx);
    d.step(consumed);

    return uc.length;
}

namespace mm {
const element_meta s_tmsi = {
    0xff,
    "5GS mobile identity - 5G-S-TMSI",
    dissect_mobile_id,
};

}
