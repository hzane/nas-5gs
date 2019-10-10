#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*The description and valid combinations of packet filter component type identifiers in a
 * packet filter are defined in 3GPP TS 23.501 [8].*/

// Figure 9.11.4.13.4 Packet filter list when the rule operation is "create new QoS rule",
// or "modify existing QoS rule and add packet filters" or "modify existing QoS rule and
// replace all packet filters"


// Authorized QoS rules QoS rules 9.11.4.13
result_t die_qos_rule(dissector d, context* ctx, qos_rule_t*ret){
    const use_context uc(&d, ctx, "qos-rule", 0);
    de_nibble(d, ctx, &ret->packet_filters_n);
    de_uint8(d, ctx, &ret->dqr, 0x10u);
    de_uint8(d, ctx, &ret->rule_operation_code, 0xc0u).step(d);

    switch (ret->rule_operation_code) {
    case 0b000:
        break;  // reserved
    case 0b001: // create new QoS rule
    case 0b011: // Modify existing QoS rule and add packet filter
    case 0b100: { // Modify existing QoS rule and replace
        qos_rule_t::packet_filter_add_t v = {};
        for (auto i = 0; i < ret->packet_filters_n; ++i) {
            de_uint8(d, ctx, &v.id, 0x0fu);
            de_uint8(d, ctx, &v.direction, 0x30u).step(d);
            de_l_octet(d, ctx, &v.content).step(d);
        }
        ret->add_packets.push_back(v);
    }
        break; //
    case 0b010:     // Delete existing QoS rule
        break;  //
    case 0b101: // Modify existing QoS rule and delete
        for (auto i = 0; i < ret->packet_filters_n;++i) {
            auto id = d.uint8(true) & 0x0fu;
            ret->delete_packets.push_back(id);
        }
        break;
    }
    if (d.length>0){
        ret->precedence.present = true;
        de_uint8(d, ctx, &ret->precedence.v).step(d);
    }
    if (d.length> 0){
        ret->qos_flow_id.present = true;
        de_uint8(d, ctx, &ret->qos_flow_id.v, 0x3fu);
        ret->segregation.present = true;
        de_uint8(d, ctx, &ret->segregation.v, 0x40u).step(d);
    }
    return {uc.length};
}

// Authorized QoS rules QoS rules 9.11.4.13
result_t die_qos_rules(dissector d, context* ctx, qos_rules_t*ret){
    const use_context uc(&d, ctx, "qos-rules", 0);
    while(d.length> 0 ){
        qos_rule_t v = {};
        v.id      = d.uint8(true);
        v.length       = d.uint8(true);
        die_qos_rule(d.slice(v.length), ctx, &v).step(d);
        ret->rules.push_back(v);
    }
    return {uc.length};
}