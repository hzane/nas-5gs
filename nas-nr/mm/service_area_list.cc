#include "../common/ber.hh"
#include "../common/definitions.hh"
#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.49    Service area list page.391
result_t die_service_area_header(dissector d, context*ctx, service_area_header_t*ret){
    de_uint8(d, ctx, &ret->number, 0x1fu);
    de_uint8(d, ctx, &ret->type, 0x60u);
    de_uint8(d, ctx, &ret->allowed_type, 0x80u).step(d);

    return {1};
}

// 9.11.3.49    Service area list page.391
result_t die_service_area_01(dissector d, context*ctx, service_area_01_t*ret){
    die_service_area_header(d, ctx, &ret->header).step(d);
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);
    de_fixed(d, ctx, ret->tac.v).step(d);
    return {7};
}
// 9.11.3.49    Service area list page.391
result_t die_service_area_00(dissector d, context*ctx, service_area_00_t*ret){
    const use_context uc(&d, ctx, "service-area-00", 0);

    die_service_area_header(d, ctx, &ret->header).step(d);

    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    for(auto i = 0; i <= ret->header.number; ++i){
        tac_t v={};
        de_fixed(d, ctx, v.v).step(d);
        ret->tacs.push_back(v);
    }
    return {uc.consumed()};
}
// 9.11.3.49    Service area list page.391
result_t die_service_area_10(dissector d, context*ctx, service_area_10_t*ret){
    const use_context uc(&d, ctx, "service-area-10", 0);
    die_service_area_header(d, ctx, &ret->header).step(d);
    for(auto i = 0; i<=ret->header.number;++i){
        service_area_10_t::area_t v = {};
        die_mcc_mnc(d, ctx, &v.mccmnc).step(d);
        de_fixed(d, ctx, v.tac.v).step(d);
        ret->value.push_back(v);
    }
    return {uc.consumed()};
}

// 9.11.3.49    Service area list page.391
result_t die_service_area_11(dissector d, context*ctx, service_area_11_t*ret){
    die_service_area_header(d, ctx, &ret->header).step(d);
    die_mcc_mnc(d, ctx, &ret->mccmnc).step(d);

    return {4};
}
// 9.11.3.49    Service area list page.391
result_t die_service_area(dissector d, context*ctx, service_area_t*ret){
    const use_context uc(&d, ctx, "service-area", 0);

    auto tl = umask(d.uint8(false), 0x60u);
    switch (tl){
    case 0b00:
        ret->l_00 = std::make_shared<service_area_00_t>();
        die_service_area_00(d, ctx, ret->l_00.get()).step(d);
        break;
    case 0b01:
        ret->l_01 = std::make_shared<service_area_01_t>();
        die_service_area_01(d, ctx, ret->l_01.get()).step(d);
        break;
    case 0b10:
        ret->l_10 = std::make_shared<service_area_10_t>();
        die_service_area_10(d, ctx, ret->l_10.get()).step(d);
        break;
    case 0b11:
        ret->l_11 = std::make_shared<service_area_11_t>();
        die_service_area_11(d, ctx, ret->l_11.get()).step(d);
        break;
    default:break;
    }

    return {uc.consumed()};
}
// 9.11.3.49    Service area list page.391
result_t die_service_area_list(dissector d, context* ctx, service_area_list_t* ret) {
    diag("de service-area-list not implemented yet");
    while(d.length>0){
        service_area_t v = {};
        die_service_area(d, ctx, &v).step(d);
        ret->partial.push_back(v);
    }
    return {d.length};
}
