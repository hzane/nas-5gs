#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"
#include "../common/dissects.hh"

//* 9.11.3.8     5GS tracking area identity
result_t die_partial_tai_list_00(dissector d, context* ctx, partial_tai_list_00_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    for (auto n = ret->number; n > 0;) {
        o3_t o3 = {};
        de_fixed(d, ctx, o3.v).step(d);
        ret->taces.push_back(o3);
        --n;
    }
    return {uc.consumed()};
}
//* 9.11.3.8     5GS tracking area identity
result_t die_partial_tai_list_01(dissector d, context* ctx, partial_tai_list_01_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac).step(d);

    for (auto n = ret->number; n > 1; --n) {
        o3_t o3 = {};
        de_fixed(d, ctx, o3.v).step(d);
        ret->others.push_back(o3);
    }

    return {uc.consumed()};
}
//* 9.11.3.8     5GS tracking area identity
result_t die_partial_tai_list_10(dissector d, context* ctx, partial_tai_list_10_t* ret) {
    const use_context uc(&d, ctx, "partial-tai-id", 0);

    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u).step(d);

    for (auto n = ret->number; n > 0;) {
        nr_tracking_area_id_t tai = {};
        die_nr_tracking_area_id(d, ctx, &tai).step(d);
        ret->ids.push_back(tai);
        --n;
    }
    return {uc.consumed()};
}

//* 9.11.3.8     5GS tracking area identity
result_t die_partial_tai(dissector d, context* ctx, partial_tai_t* ret) {
    const use_context uc(&d, ctx, "partial-tai", -1);

    ret->type = mask_u8(d.uint8(false), 0x60u);
    if (ret->type == 0) {
        ret->l00 = std::make_shared< partial_tai_list_00_t >();
        die_partial_tai_list_00(d, ctx, ret->l00.get()).step(d);
    }
    if (ret->type == 1) {
        ret->l01 = std::make_shared< partial_tai_list_01_t >();
        die_partial_tai_list_01(d, ctx, ret->l01.get()).step(d);
    }
    if (ret->type == 2) {
        ret->l10 = std::make_shared< partial_tai_list_10_t >();
        die_partial_tai_list_10(d, ctx, ret->l10.get()).step(d);
    }

    return {uc.consumed()};
}

//* 9.11.3.8     5GS tracking area identity
result_t die_nr_tracking_id_list(dissector                   d,
                                 context*                    ctx,
                                 nr_tracking_area_id_list_t* ret) {
    const use_context uc(&d, ctx, "nr-tracking-area-id-list", 0);

    while (d.length > 0) {
        partial_tai_t ptai = {};
        die_partial_tai(d, ctx, &ptai).step(d);
        ret->partials.push_back(ptai);
    }
    return {uc.length};
}
/* 9.11.3.30    LADN information  */
/*Figure 9.11.3.30.1: LADN information information element
8	7	6	5	4	3	2	1
Length of DNN value	octet 4
DNN value	octet 5  octet m
5GS tracking area identity list	octet m+1  octet a
*/
result_t die_ladn(dissector d, context* ctx, ladn_information_t::ladn_t* ret) {
    const use_context uc(&d, ctx, "ladn-information-entry", 0);

    auto dl = d.uint8(true);
    de_octet(d.slice(dl), ctx, &ret->dnn).step(d);

    auto tl = d.uint8(true);
    die_nr_tracking_id_list(d.slice(tl), ctx, &ret->ntai).step(d);

    return {uc.length};
}

result_t dissect_ladn_information(dissector d, context* ctx, ladn_information_t* ret) {
    const use_context uc(&d, ctx, "ladn-information", 0);

    while (d.length > 0) {
        ladn_information_t::ladn_t ladn = {};
        die_ladn(d, ctx, &ladn).step(d);
        ret->ladns.push_back(ladn);
    }
    return {uc.length};
}
