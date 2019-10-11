#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.61	Mobile station classmark 2
// See subclause 10.5.1.6 in 3GPP TS 24.008 [12].
result_t die_mobile_station_classmark2(dissector d, context*ctx, mobile_station_classmark2_t*ret){
    const use_context uc(&d, ctx, "mobile-station-classmark2", 0);
    de_uint8(d, ctx, &ret->rf_power_capability, 0x07u);
    de_uint8(d, ctx, &ret->a51, 0x08u);
    de_uint8(d, ctx, &ret->es_ind, 0x10u);
    de_uint8(d, ctx, &ret->revision_level, 0x60u).step(d);

    de_uint8(d, ctx, &ret->fc, 0x01u);
    de_uint8(d, ctx, &ret->vgcs, 0x02u);
    de_uint8(d, ctx, &ret->vbs, 0x04u);
    de_uint8(d, ctx, &ret->sm_capability, 0x08u);
    de_uint8(d, ctx, &ret->ss_screen_ind, 0x30u);
    de_uint8(d, ctx, &ret->ps_capability, 0x40u).step(d);

    de_uint8(d, ctx, &ret->a52, 0x01u);
    de_uint8(d, ctx, &ret->a53, 0x02u);
    de_uint8(d, ctx, &ret->cmsp, 0x04u);
    de_uint8(d, ctx, &ret->solsa, 0x08u);
    de_uint8(d, ctx, &ret->ucs2, 0x10u);
    de_uint8(d, ctx, &ret->lcsvacap, 0x20u);
    de_uint8(d, ctx, &ret->cm3, 0x80u).step(d);

    return {uc.length};
}