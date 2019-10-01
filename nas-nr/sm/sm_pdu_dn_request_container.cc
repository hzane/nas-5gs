#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

// SM PDU DN request container 9.11.4.15
int sm::dissect_pdu_dn_request_container(dissector d, context* ctx) {
    const use_context uc(ctx, "dn-specific-container", d, 0);

    // A DN-specific identity of the UE in the network access identifier (NAI)
    // format according to IETF RFC 7542 [37], encoded as UTF-8 string.
    auto v = string((const char*) d.ptr(), d.length);
    d.add_item(d.length, "DN-specific identity", v);

    return uc.length;
}
