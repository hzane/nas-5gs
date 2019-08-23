#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_authentication_rej{

}
/*
 * 8.2.5 Authentication reject
 */
int mm::authentication_rej(dissector d, context* ctx) {
    use_context uc(ctx, "authentication-reject");

    using namespace mm_authentication_rej;

    /* 78    EAP message    EAP message 9.11.2.2    O    TLV-E    7-1503 */
    // ELEM_OPT_TLV_E(0x78, NAS_5GS_PDU_TYPE_COMMON, DE_NAS_5GS_CMN_EAP_MESSAGE, NULL);

    extraneous_data_check(d.pinfo, d.tree, d.tvb, d.offset, d.length, 0);
    return d.tvb->reported_length;
}
namespace mm_authentication_rej {

}
