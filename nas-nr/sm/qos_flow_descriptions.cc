#include "../common/dissector.hh"
#include "../common/use_context.hh"


int dissect_qos_parameters(dissector d, int j, context* ctx) {
    const use_context uc(&d, ctx, "qos-param", -1);

    return 0;
}

// Authorized QoS flow descriptions     QoS flow descriptions 9.11.4.12
int dissect_authorized_qos_flow_description(dissector d, context* ctx) {
    const use_context uc(&d, ctx, "authorized-qos-flow-desc", 0);
    return 0;
}
