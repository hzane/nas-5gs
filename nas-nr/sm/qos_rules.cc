#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*The description and valid combinations of packet filter component type identifiers in a
 * packet filter are defined in 3GPP TS 23.501 [8].*/
int dissect_packet_filter(dissector d, int pf_type, context* ctx) {
    const use_context uc(&d, ctx, "packet-filter", -1);

    return 0;
}

// Figure 9.11.4.13.4 Packet filter list when the rule operation is "create new QoS rule",
// or "modify existing QoS rule and add packet filters" or "modify existing QoS rule and
// replace all packet filters"
int dissect_packet_filters(dissector d, int rop, context* ctx) {
    (void) rop;

    const use_context uc(&d, ctx, "packet-filters", -1);


    return 0;
}

// Authorized QoS rules QoS rules 9.11.4.13
int dissect_qos_rules(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "authorized-qos-rules",0);


    return uc.length;
}

// Authorized QoS rules QoS rules 9.11.4.13
int dissect_authorized_qos_rules(dissector d, context* ctx) {
    return dissect_qos_rules(d, ctx);
}
