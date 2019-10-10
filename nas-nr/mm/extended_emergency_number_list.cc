#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// Extended emergency number list  9.11.3.26
// See subclause 9.9.3.37A in 3GPP TS 24.301 [15].
result_t die_sub_service(dissector                                    d,
                         context*                                     ctx,
                         extended_emergency_number_list_t::service_t* ret) {
    static const char bcds[] = "0123456789????\0";
    auto              nlen   = d.uint8(true);
    for (auto i = nlen; i > 0; --i) {
        auto o = d.uint8(true);
        ret->digits.push_back(bcds[mask_u8(o, 0x0fu)]);
        ret->digits.push_back(bcds[mask_u8(0, 0xf0u)]);
    }

    auto slen              = d.uint8(true);
    ret->sub_service_field = string((const char*) d.safe_ptr(), d.safe_length(slen));
    d.step(slen);

    return {1 + nlen + 1 + slen};
}

// Extended emergency number list  9.11.3.26
// See subclause 9.9.3.37A in 3GPP TS 24.301 [15].
result_t die_extended_emergency_number_list(dissector                         d,
                                            context*                          ctx,
                                            extended_emergency_number_list_t* ret) {
    auto len   = d.length;
    ret->eenlv = d.uint8(true) & 0x01u;

    while (d.length > 0) {
        extended_emergency_number_list_t::service_t svc = {};
        die_sub_service(d, ctx, &svc).step(d);
        ret->services.push_back(svc);
    }
    return {len};
}
