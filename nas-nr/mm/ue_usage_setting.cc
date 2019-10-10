#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.55
result_t die_ue_usage_setting(dissector d, context* ctx, ue_usage_setting_t* ret) {
    ret->setting = d.uint8(true) & 0x01u;

    return {1};
}