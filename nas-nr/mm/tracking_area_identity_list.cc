#include "../common/dissect_mm_msg.hh"

using namespace cmn;


// 9.11.3.9	5GS tracking area identity list
int mm::dissect_tracking_area_id_list(dissector d, context* ctx) {
    const use_context uc(ctx, "5gs-tai-list", d, 0);

    static const field_meta* flags[] = {
        &hf_tracking_area_list_type,
        &hf_tracking_area_list_number,
        nullptr,
    };

    auto consumed = 0;
    auto n        = 1;
    /*Partial tracking area list*/
    while (d.length > 0) {
        const auto orig_offset = d.offset;
        auto       subtree     = d.add_tree(-1, formats("Partial tracking area list  %u", n++));
        use_tree   ut(d, subtree);

        /*Head of Partial tracking area list*/
        /* Type of list    Number of elements    octet 1 */
        const auto head  = d.tvb->uint8(d.offset);
        const auto li    = (head & 0x60u) >> 5u;
        auto       num_e = (head & 0x1fu) + 1;
        d.add_bits(flags);
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
                (void) d.add_item(3, &hf_tracking_area_code, enc::be);
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
            (void) d.add_item(3, &hf_tracking_area_code, enc::be);
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
                (void) d.add_item(3, &hf_tracking_area_code, enc::be);
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
