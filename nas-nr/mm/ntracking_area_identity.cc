#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

//* 9.11.3.8     5GS tracking area identity
result_t die_nr_tracking_area_id(dissector d, context* ctx, nr_tracking_area_id_t* ret) {
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac).step(d);

    return {6};
}
