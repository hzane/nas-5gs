#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

inline const sms_field hf_dn_specific_identity = {
    "DN-specific identity",
};
// SM PDU DN request container 9.11.4.15
int sm::dissect_pdu_dn_request_container(dissector d, context* ctx) {
    const use_context uc(ctx, "dn-specific-container", d, 0);

    // A DN-specific identity of the UE in the network access identifier (NAI)
    // format according to IETF RFC 7542 [37], encoded as UTF-8 string.
    d.add_item(&hf_dn_specific_identity, d.length, true);

    return uc.length;
}
