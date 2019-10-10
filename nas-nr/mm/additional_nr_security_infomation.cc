#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// * 9.11.3.12    Additional 5G security information
result_t die_additional_nr_security_infomation(
    dissector                             d,
    context*                              ctx,
    additional_nr_security_information_t* ret) {
    de_uint8(d, ctx, &ret->hdp, 0x01);
    de_uint8(d, ctx, &ret->rinmr, 0x02).step(d);

    return {1};
}
