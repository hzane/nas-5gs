#include "../common/dissect_mm_msg.hh"

using namespace cmn;

// 9.11.3.49    Service area list page.391
int mm::dissect_service_area_list(dissector d, context* ctx) {
    const use_context        uc(ctx, "service-area-list", d, 0);

    static const field_meta* flags[] = {
        &hf_sal_allowed_type,
        &hf_sal_list_type,
        &hf_element_number,
        nullptr,
    };
    auto n = 1;
    /*Partial service area list*/
    while (d.length > 0) {
        const auto     start   = d.offset;
        const auto     subtree = d.add_tree(-1, formats("Partial service area list  %u", n++));
        use_tree ut(d, subtree);

        /*Head of Partial service area list*/
        /* Allowed type    Type of list    Number of elements    octet 1 */
        const auto sal_head  = d.tvb->uint8(d.offset);
        const auto sal_t_li  = (sal_head & 0x60u) >> 5u;
        auto sal_num_e = (sal_head & 0x1f) + 1;
        d.add_bits(flags);
        d.step(1);

        switch (sal_t_li) {
        case 0: {
            // type of list = "00"
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
            while (sal_num_e > 0) {
                (void) d.add_item(3, &hf_tracking_area_code, enc::be);
                d.step(3);
                --sal_num_e;
            }
        } break;
        case 1: {
            // type of list = "01"
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);

            /*octet 5  TAC 1*/
            (void) d.add_item(3, &hf_tracking_area_code, enc::be);
            d.step(3);
        } break;
        case 2: {
            // type of list = "10"
            while (sal_num_e > 0) {
                dissect_e212_mcc_mnc(d, ctx);
                d.step(3);

                /*octet 5  TAC 1*/
                (void) d.add_item(3, &hf_tracking_area_code, enc::be);
                d.step(3);
                --sal_num_e;
            }
        } break;
        case 3: {
            // type of list = "11"
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
        } break;
        default: // never goes here
            break;
        }

        /*calculate the length of IE */
        d.tree->set_length(d.offset - start);
        /*calculate the number of Partial service area list*/
    }
    return uc.length;
}

/*  9.11.3.49    Service area list */
extern const value_string nas_5gs_mm_sal_t_li_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};

const tf_string tfs_tai_or_not = {
    "TAIs in the list are in the non-allowed area",
    "TAIs in the list are in the allowed area",
};

const field_meta mm::hf_sal_allowed_type= {
    "Allowed type",
    "nas.nr.mm.sal_al_t",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_tai_or_not,
    nullptr,
    0x80,
};
const field_meta mm::hf_sal_list_type = {
    "Type of list",
    "nas.nr.mm.sal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_sal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
