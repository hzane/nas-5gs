#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_id {
extern const element_meta id_type;
}
using namespace nas;
using namespace mm;

/*
 * 8.2.21 Identity request
 */
int mm::id_req(dissector d, context* ctx) {
    const auto        len = d.length;
    use_context uc(ctx, "identity-request", d);

    using namespace mm_id;

    /* Identity type    5GS identity type 9.11.3.3    M    V    1/2 */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    // ELEM_MAND_V(,ei_nas_5gs_missing_mandatory_elemen);
    const auto consumed = dissect_elem_v(nullptr, &id_type, d, ctx);
    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    d.step(consumed);

    d.extraneous_data_check(0);
    return len;
}

namespace {
/* * 9.11.3.4    5GS mobile identity */
static const val_string type_id_values[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0, nullptr},
};
}
namespace mm_id {
int dissect_id_type(dissector d, context* ctx);

extern const element_meta id_type = {
    0xff,
    "Identity type",
    dissect_id_type,
    nullptr,
};


/* * 9.11.3.3 5GS identity type */
const field_meta hf_id_type = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    type_id_values,
    nullptr,
    nullptr,
    0x07,
};

/* 9.11.3.4    5GS mobile identity */

/* * 9.11.3.3 5GS identity type */
int dissect_id_type(dissector d, context* ctx) {
    d.add_item(1, &hf_id_type, enc::be);
    return 1; }
} // namespace mm_id_req
