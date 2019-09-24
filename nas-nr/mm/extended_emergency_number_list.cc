#include "../common/dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

const element_meta mm::ext_emergency_number_list = {
    0x7A,
    "Extended emergency number list",
    dissect_extended_emergency_number_list,
    nullptr,
};

// Extended emergency number list  9.11.3.26
int mm::dissect_extended_emergency_number_list(dissector d, context* ctx) {
    // See subclause 9.9.3.37A in 3GPP TS 24.301 [15].
    const use_context uc(ctx, "extended-emergency-number-list", d, 0);

    (void) d.add_item(1, &hf_ext_emergency_number_list_validity, enc::be);
    d.step(1);

    auto i = 1;
    while (d.length > 0) {
        const auto start   = d.offset;
        auto       subtree = d.add_tree(-1, formats("Extended emergency number #%u", i++));
        use_tree   ut(d, subtree);

        auto length = static_cast< int >(d.uint8());
        (void) d.add_item(1, &hf_ext_emerge_num_len, enc::be);
        d.step(1);

        if (length > 0) {
            (void) d.add_item(length, &hf_emergency_number, enc::be);
            d.step(length);
        }

        length = d.uint8();
        (void) d.add_item(1, &hf_sub_services_field_length, enc::be);
        d.step(1);

        if (length > 0) {
            (void) d.add_item(length, &hf_sub_services_field, enc::be);
            d.step(length);
        }
        subtree->set_length(d.offset - start);
    }

    return uc.length;
}
struct extended_emergency_number_t {
    std::vector< uint8_t > number;
    std::vector< uint8_t > field;
};
struct extended_emergency_number_list_t {
    uint8_t validity;
    std::vector< extended_emergency_number_t > numbers;
};
