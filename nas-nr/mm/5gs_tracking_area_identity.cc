#include "../dissect_mm_msg.hh"

using namespace cmn;


//* 9.11.3.8     5GS tracking area identity
int mm::dissect_last_visited_tai(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-tracking area identity", d, -1);

    dissect_e212_mcc_mnc(d, ctx);
    d.step(3);

    /* TAC Octet 5 - 7 */
    (void) d.add_item(3, &hf_tac, enc::na);

    return 6;
}
struct last_visit_tracking_area_identity_t{
    string mcc;
    string mnc;
    uint8_t tac[3];
};

/*  9.11.3.9     5GS tracking area identity list */
extern const value_string tracking_area_identity_list_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0, nullptr},
};

extern const value_string nas_5gs_mm_tal_num_e[] = {
    {0x00, "1 element"},
    {0x01, "2 elements"},
    {0x02, "3 elements"},
    {0x03, "4 elements"},
    {0x04, "5 elements"},
    {0x05, "6 elements"},
    {0x06, "7 elements"},
    {0x07, "8 elements"},
    {0x08, "9 elements"},
    {0x09, "10 elements"},
    {0x0a, "11 elements"},
    {0x0b, "12 elements"},
    {0x0c, "13 elements"},
    {0x0d, "14 elements"},
    {0x0e, "15 elements"},
    {0x0f, "16 elements"},
    {0, nullptr},
};
const field_meta mm::hf_tal_t_li = {
    "Type of list",
    "nas.nr.mm.tracking.area.type",
    ft::ft_uint8,
    fd::base_dec,
    tracking_area_identity_list_values,
    nullptr,
    nullptr,
    0x60,
};
const field_meta mm::hf_tal_num_e = {
    "Number of elements",
    "nas.nr.number",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_tal_num_e,
    nullptr,
    nullptr,
    0x1f,
};
const field_meta mm::hf_tac = {
    "TAC",
    "nas.nr.tac",
    ft::ft_uint24,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
