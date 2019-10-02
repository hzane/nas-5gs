#include "../common/dissector.hh"
#include "../common/use_context.hh"

// SM PDU DN request container 9.11.4.15
int dissect_pdu_dn_request_container(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "dn-specific-container", 0);

    // A DN-specific identity of the UE in the network access identifier (NAI)
    // format according to IETF RFC 7542 [37], encoded as UTF-8 string.

    return uc.length;
}
