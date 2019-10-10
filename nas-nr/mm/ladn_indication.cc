#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*  9.11.3.29    LADN indication  */
result_t die_ladn_indication(dissector d, context* ctx, ladn_indication_t* ret) {
    auto len = d.length;
    while (d.length > 0) {
        auto l = d.uint8(true);
        ret->dnns.emplace_back(d.safe_ptr(), d.safe_ptr() + d.safe_length(l));
    }
    return {len};
}
