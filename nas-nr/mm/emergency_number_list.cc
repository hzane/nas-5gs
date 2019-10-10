#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// Emergency number list  9.11.3.23
result_t die_number(dissector d, context* ctx, emergency_number_list_t::number_t* ret) {
    static char bcds[] = "0123456789????\0";
    auto        len    = d.length;
    de_uint8(d, ctx, &ret->service_category).step(d);
    while (d.length > 0) {
        auto o = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(o, 0x0f)]);
        ret->digits.push_back(bcds[mask_u8(0, 0xf0u)]);
    }
    return {len};
}

// Emergency number list  9.11.3.23
result_t die_emergency_number_list(dissector                d,
                                   context*                 ctx,
                                   emergency_number_list_t* ret) {
    const use_context uc(&d, ctx, "emergency-number-list", 0);
    while (d.length > 0) {
        auto                              len = d.uint8(true);
        emergency_number_list_t::number_t n   = {};
        die_number(d.slice(len), ctx, &n).step(d);
        ret->numbers.push_back(n);
    }
    return {uc.length};
}
