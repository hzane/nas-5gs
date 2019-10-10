#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/*
9.11.3.9A	5GS update type
*/
result_t die_nr_update_type(dissector d, context* ctx, nr_update_type_t* ret) {
    const use_context uc(&d, ctx, "nr-update-type", 0);
    de_uint8(d, ctx, &ret->sms_requested, 0x01);
    de_uint8(d, ctx, &ret->nran_rcu, 0x02);
    de_uint8(d, ctx, &ret->pnb_ciot, 0x0c).step(d);

    return {1};
}
