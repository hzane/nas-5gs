#include "../dissect_sm_msg.hh"

extern const element_meta sm::requested_qos_rules = {
    0x7A,
    "Requested QoS rules",
    dissect_requested_qos_rules,
    nullptr,

};
/*  9.11.4.13    QoS rules */
const true_false_string sm::tfs_nas_5gs_sm_dqr = {
    "The QoS rule is the default QoS rule",
    "The QoS rule is not the default QoS rule",
};

extern const value_string nas_5gs_rule_operation_code_values[] = {
    {0x0, "Reserved"},
    {0x1, "Create new QoS rule"},
    {0x2, "Delete existing QoS rule"},
    {0x3, "Modify existing QoS rule and add packet filters"},
    {0x4, "Modify existing QoS rule and replace packet filters"},
    {0x5, "Modify existing QoS rule and delete packet filters"},
    {0x6, "Modify existing QoS rule without modifying packet filters"},
    {0x7, "Reserved"},
    {0, nullptr},
};
