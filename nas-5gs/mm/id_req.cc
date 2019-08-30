#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_id {
extern const element_meta id_type;
}
using namespace nas;

/*
 * 8.2.21 Identity request
 */
int mm::id_req(dissector d, context* ctx) {
    use_context uc(ctx, "identity-request");

    using namespace mm_id;

    /*     Identity type    5GS identity type 9.11.3.3    M    V    1/2 */
    /* Spare half octet    Spare half octet 9.5    M    V    1/2 */
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_spare_half_octet, enc::be);
    // ELEM_MAND_V(DE_NAS_5GS_MM_5GS_IDENTITY_TYPE,ei_nas_5gs_missing_mandatory_elemen);
    auto consumed = dissect_elem_v(nullptr, &id_type, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return d.tvb->length;
}

namespace mm_id {
int                       dissect_id_type(dissector d, context* ctx);
extern const element_meta id_type = {
    0xff,
    "Identity type",
    dissect_id_type,
};

/*
 * 9.11.3.4    5GS mobile identity
 */
const value_string nas_5gs_mm_type_id_vals[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0, nullptr},
};
/*
 * 9.11.3.3 5GS identity type
 */
const field_meta hf_id_type = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_type_id_vals,
    nullptr,
    nullptr,
    0x07,
};
int dissect_id_type(dissector d, context* ctx) {
    d.add_item(1, &hf_id_type, enc::be);
    return 1; }
} // namespace mm_id_req
