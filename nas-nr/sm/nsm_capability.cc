#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*  9.11.4.1    5GSM capability */
result_t die_nsm_capability(dissector d, context*ctx, nsm_capability_t*ret){
    de_uint8(d, ctx, &ret->rqos, 0x01u);
    de_uint8(d, ctx, &ret->mh6_pdu, 0x02u);
    de_uint8(d, ctx, &ret->ept_s1, 0x04u);
    de_uint8(d, ctx, &ret->ats_ll, 0x08u);
    de_uint8(d, ctx, &ret->mptcp, 0x10u).step(d);
    return {1};
}