#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;


//* 9.11.3.8     5GS tracking area identity
int mm::dissect_last_visited_tai(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-tracking area identity", d, -1);

    dissect_e212_mcc_mnc(d, ctx);
    d.step(3);

    /* TAC Octet 5 - 7 */
    (void) d.add_item(3, &hf_tracking_area_code);

    return 6;
}


/*  9.11.3.9     5GS tracking area identity list */
extern const value_string tracking_area_identity_list_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0, nullptr},
};

extern const value_string tracking_area_list_number_values[] = {
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
const tag_field mm::hf_tracking_area_list_type = {
    "Type of list",
    0x60,
    tracking_area_identity_list_values,
};
const tag_field mm::hf_tracking_area_list_number = {
    "Number of elements",
    0x1f,
    tracking_area_list_number_values,
};

// TAC, Tracking area code
const uint24_field mm::hf_tracking_area_code = {
    "TAC, Tracking area code",
    0x0,
};
