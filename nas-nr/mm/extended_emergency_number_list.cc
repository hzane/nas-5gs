#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;


const bool_field hf_ext_emergency_number_list_validity = {
    "Extended Emergency Number List Validity",
    0x01,
    "Valid in the country of the PLMN from which this IE is received",
    "Valid only in the PLMN from which this IE is received",
};


const uint8_field hf_ext_emerge_num_len = {
    "Emergency number information length",
    0x0,
};

const bcd_field hf_emergency_number = {
    "Emergency number",
};

const uint8_field hf_sub_services_field_length = {
    "Sub-services field length",
    0x0,
};

const sms_field hf_sub_services_field = {
    "Sub-services field",
};


// Extended emergency number list  9.11.3.26
int mm::dissect_extended_emergency_number_list(dissector d, context* ctx) {
    // See subclause 9.9.3.37A in 3GPP TS 24.301 [15].
    const use_context uc(ctx, "extended-emergency-number-list", d, 0);

    (void) d.add_item(&hf_ext_emergency_number_list_validity);
    d.step(1);

    auto i = 1;
    while (d.length > 0) {
        const auto start   = d.offset;
        auto       subtree = d.add_item(-1, formats("Extended emergency number #%u", i++));
        use_tree   ut(d, subtree);

        auto length = static_cast< int >(d.uint8());
        (void) d.add_item( &hf_ext_emerge_num_len);
        d.step(1);

        if (length > 0) {
            (void) d.add_item(&hf_emergency_number, length);
            d.step(length);
        }

        length = d.uint8();
        (void) d.add_item(&hf_sub_services_field_length);
        d.step(1);

        if (length > 0) {
            (void) d.add_item(&hf_sub_services_field, length);
            d.step(length);
        }
        subtree->set_length(d.offset - start);
    }

    return uc.length;
}
