#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
result_t die_qos_flow_description(dissector                         d,
                                  context*                          ctx,
                                  qos_flow_descriptions_t::entry_t* ret) {
    const use_context uc(&d, ctx, "qos-flow-description", 0);
    de_uint8(d, ctx, &ret->qfi, 0x3fu).step(d);
    de_uint8(d, ctx, &ret->opcode, 0xc0u).step(d);
    de_uint8(d, ctx, &ret->ebit, 0x40u);
    auto n = d.uint8(true) & 0x3fu;
    for (auto i = 0; i < n; ++i) {
        qos_flow_descriptions_t::parameter_t v = {};
        de_uint8(d, ctx, &v.id).step(d);
        de_l_octet(d, ctx, &v.content);
        ret->parameters.push_back(v);
    }
    return {uc.consumed()};
}
result_t dei_qos_flow_descriptions(dissector d, context* ctx, qos_flow_descriptions_t*ret){
    const use_context uc(&d, ctx, "qos-flow-descriptions", 0);
    while(d.length> 0 ){
        qos_flow_descriptions_t::entry_t v = {};
        die_qos_flow_description(d, ctx, &v).step(d);
        ret->descs.push_back(v);
    }
    return {uc.length};
}