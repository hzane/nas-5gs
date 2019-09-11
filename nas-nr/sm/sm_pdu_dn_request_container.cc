#include "../dissect_sm_msg.hh"

// SM PDU DN request container 9.11.4.15
const element_meta sm::sm_pdu_dn_req_cont = {
    0x39u,
    "PDU DN request container",
    sm::dissect_pdu_dn_req_cont,
    nullptr,
};
const field_meta hf_dn_spec_id = {
    "DN-specific identity",
    "nas.nr.sm.dnreq.dnspec.id",
    ft::ft_bytes,
    fd::base_string,
    nullptr,
    nullptr,
    nullptr,
    0,
};

// SM PDU DN request container 9.11.4.15
int sm::dissect_pdu_dn_req_cont(dissector d, context* ctx) {
    const use_context uc(ctx, "dn-specific-identity", d, 0);

    // A DN-specific identity of the UE in the network access identifier (NAI)
    // format according to IETF RFC 7542 [37], encoded as UTF-8 string.
    d.add_item(d.length, &hf_dn_spec_id, enc::be);
    d.step(d.length);

    return uc.length;
}
