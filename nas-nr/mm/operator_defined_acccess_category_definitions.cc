#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  9.11.3.38    Operator-defined access category definitions */
result_t die_operator_defined_access_category_definition(
    dissector                                      d,
    context*                                       ctx,
    operator_defined_access_category_definition_t* ret) {
    const use_context uc(&d, ctx, "operator-defined-access-category-definition", 0);
    de_uint8(d, ctx, &ret->precedence).step(d);

    de_uint8(d, ctx, &ret->psac, 0x80u);
    de_uint8(d, ctx, &ret->number, 0x1fu).step(d);

    de_l_octet(d, ctx, &ret->criteria).step(d);
    if (d.length > 0) {
        ret->standardized_access_category.present = true;
        de_uint8(d, ctx, &ret->standardized_access_category.v, 0x1fu).step(d);
    }
    return {uc.length};
}

/*  9.11.3.38    Operator-defined access category definitions */
result_t die_operator_defined_access_category_definitions(
    dissector                                       d,
    context*                                        ctx,
    operator_defined_access_category_definitions_t* ret) {
    const use_context uc(&d, ctx, "operator-defined-access-category-definitions", 0);
    while (d.length > 0) {
        auto                                          l = d.uint8(true);
        operator_defined_access_category_definition_t v = {};
        die_operator_defined_access_category_definition(d.slice(l), ctx, &v).step(d);
        ret->definitions.push_back(v);
    }
    return {uc.length};
}
