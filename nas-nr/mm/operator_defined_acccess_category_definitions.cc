#include "../common/dissector.hh"
#include "../common/use_context.hh"

/*  9.11.3.38    Operator-defined access category definitions */
int dissect_operator_defined_access_category_definitions(dissector d, context* ctx) {
    const use_context uc(ctx, "operator-defined-access-category-definitions", d, 0);

    return uc.length;
}
