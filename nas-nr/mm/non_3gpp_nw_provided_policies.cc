#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.58	Non-3GPP NW provided policies
// See subclause 10.5.5.37 in 3GPP TS 24.008
result_t die_n3gpp_nw_provided_policies(dissector                     d,
                                        context*                      ctx,
                                        n3gpp_nw_provided_policies_t* ret) {
    ret->n3en_ind = d.uint8(true) & 0x1u;
    return {1};
}
