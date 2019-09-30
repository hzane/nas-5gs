#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


/*  9.11.3.9     5GS tracking area identity list */
extern const v_string tracking_area_identity_list_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0, nullptr},
};

const tag_field hf_tracking_area_list_type = {
    "Type of list",
    0x60,
    tracking_area_identity_list_values,
};


extern const v_string tracking_area_list_number_values[] = {
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

const tag_field hf_tracking_area_list_number = {
    "Number of elements",
    0x1f,
    tracking_area_list_number_values,
};

extern const uint24_field hf_tracking_area_code;

// 9.11.3.9	5GS tracking area identity list
int mm::dissect_tracking_area_id_list(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-tai-list", d, 0);

    auto consumed = 0;
    auto n        = 1;
    /*Partial tracking area list*/
    while (d.length > 0) {
        const auto orig_offset = d.offset;
        auto       subtree     = d.add_item(-1, formats("Partial tracking area list  %u", n++));
        use_tree   ut(d, subtree);

        /*Head of Partial tracking area list*/
        /* Type of list    Number of elements    octet 1 */
        const auto head  = d.tvb->uint8(d.offset);
        const auto li    = (head & 0x60u) >> 5u;
        auto       num_e = (head & 0x1fu) + 1;

        d.add_item(&hf_tracking_area_list_type);
        d.add_item(&hf_tracking_area_list_number);

        d.step(1);

        switch (li) {
        case 0:
            // 00
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            while (num_e > 0) {
                (void) d.add_item(&hf_tracking_area_code);
                d.step(3);

                --num_e;
            }

            break;
        case 1:
            // 01
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            /*octet 5  TAC 1*/
            (void) d.add_item(&hf_tracking_area_code);
            d.step(3);

            break;
        case 2:
            // 10
            while (num_e > 0) {
                /*octet 2  MCC digit2  MCC digit1*/
                /*octet 3  MNC digit3  MCC digit3*/
                /*octet 4  MNC digit2  MNC digit1*/
                consumed = dissect_e212_mcc_mnc(d, ctx);
                d.step(consumed);

                /*octet 5  TAC 1*/
                (void) d.add_item(&hf_tracking_area_code);
                d.step(3);

                --num_e;
            }
            break;
        case 3:
            // All other values are reserved.
            // not defined in 24.501 16.1.0
            consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);
            break;
        default:
            diag("reserved type of list %d\n", li);
            d.step(d.length); // consumed all left bytes
            break;
        }

        subtree->set_length(d.offset - orig_offset);
        /*calculate the number of Partial tracking area list*/
    }
    return uc.length;
}
