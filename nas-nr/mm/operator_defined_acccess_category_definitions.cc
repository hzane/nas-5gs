#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

extern const element_meta mm::operator_defined_access_category_defs = {
    0x76,
    "Operator-defined access category definitions",
    dissect_operator_defined_access_category_definitions,
    nullptr,

};

/*  9.11.3.38    Operator-defined access category definitions */
int mm::dissect_operator_defined_access_category_definitions(dissector d, context* ctx) {
    const use_context uc(ctx, "operator-defined-access-category-definitions", d, 0);

    auto i = 1;
    while (d.length > 0) {
        const auto length  = static_cast< int >(d.tvb->uint8(d.offset));
        auto       sd      = d.slice(length + 1);
        const auto subtree = d.add_item(
            length + 1, "Operator-defined access category definition  %u", i++);
        use_tree    ut(sd, subtree);
        use_context suc(ctx, "operator-defined-access-category-definition", sd, 0);

        // auto n = sd.add_item(1, &hf_mm_length, enc::be);
        sd.step(1);

        /* Precedence value */
        (void) sd.add_item(1, &hf_precedence, enc::be);
        sd.step(1);

        /* PSAC    0 Spare    0 Spare    Operator-defined access category number */
        const auto psac = (sd.uint8() & 0x80u);
        (void) sd.add_item(1, &hf_access_cat_n, enc::be);
        (void) sd.add_item(1, &hf_psac, enc::be);
        sd.step(1);

        /* Length of criteria */
        const auto cl = static_cast< int >(sd.uint8());
        // n             = sd.add_item(1, &hf_criteria_length, enc::be);
        sd.step(1);

        /* Criteria */
        (void) sd.add_item(cl, &hf_criteria, enc::na);

        /* Spare Spare Spare    Standardized access category a* */
        if (psac) {
            (void) sd.add_item(1, &hf_standardize_access_cat, enc::be);
            sd.step(1);
        }

        d.step(length + 1);
    }
    return uc.length;
}

// Operator-defined access category number
const field_meta mm::hf_access_cat_n = {
    "Operator-defined access category number",
    "nas.nr.mm.conf.update.operator.access.category.number",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
const tf_string tfs_standardized_category_field = {
    "Standardized access category field is included",
    "Standardized access category field is not included",
};

const field_meta mm::hf_psac = {
    "Presence of standardized access category (PSAC)",
    "nas.nr.mm.conf.update.operator.access.category.psac",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_standardized_category_field,
    nullptr,
    0x80,
};

const field_meta mm::hf_precedence = {
    "Precedence",
    "nas.nr.mm.precedence",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

#if 0
const field_meta mm::hf_criteria_length = {
    "Length",
    "nas.nr.mm.conf.update.operator.access.criteria.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0,
};
#endif

const field_meta mm::hf_criteria = {
    "Criteria",
    "nas.nr.mm.conf.update.operator.access.criteria",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0,
};

const field_meta mm::hf_standardize_access_cat = {
    "Standardized access category",
    "nas.nr.mm.conf.update.operator.access.category.type",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x1f,
};
