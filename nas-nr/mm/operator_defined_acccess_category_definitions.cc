#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace nas;
using namespace mm;

// Operator-defined access category number
const uint8_field hf_access_cat_n = {
    "Operator-defined access category number",
    0x1f,
};

const bool_field hf_psac = {
    "Presence of standardized access category (PSAC)",
    0x80,
    "Standardized access category field is not included",
    "Standardized access category field is included",
};

const uint8_field hf_precedence = {
    "Precedence",
    0x0,
};

const octet_field hf_criteria = {
    "Criteria",
};

const uint8_field hf_standardize_access_cat = {
    "Standardized access category",
    0x1f,
};

/*  9.11.3.38    Operator-defined access category definitions */
int mm::dissect_operator_defined_access_category_definitions(dissector d, context* ctx) {
    const use_context uc(ctx, "operator-defined-access-category-definitions", d, 0);

    auto i = 1;
    while (d.length > 0) {
        const auto length  = static_cast< int >(d.tvb->uint8(d.offset));
        auto       sd      = d.slice(length + 1);
        const auto subtree = d.add_item(
            length + 1, formats("Operator-defined access category definition  %u", i++));
        use_tree    ut(sd, subtree);
        use_context suc(ctx, "operator-defined-access-category-definition", sd, 0);

        // auto n = sd.add_item(1, &hf_mm_length);
        sd.step(1);

        /* Precedence value */
        (void) sd.add_item(&hf_precedence);
        sd.step(1);

        /* PSAC    0 Spare    0 Spare    Operator-defined access category number */
        const auto psac = (sd.uint8() & 0x80u);
        (void) sd.add_item( &hf_access_cat_n);
        (void) sd.add_item( &hf_psac);
        sd.step(1);

        /* Length of criteria */
        const auto cl = static_cast< int >(sd.uint8());
        // n             = sd.add_item(1, &hf_criteria_length);
        sd.step(1);

        /* Criteria */
        (void) sd.add_item(&hf_criteria, cl);

        /* Spare Spare Spare    Standardized access category a* */
        if (psac) {
            (void) sd.add_item( &hf_standardize_access_cat);
            sd.step(1);
        }

        d.step(length + 1);
    }
    return uc.length;
}

