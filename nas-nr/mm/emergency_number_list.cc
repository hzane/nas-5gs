#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

const bcd_field hf_emergency_number_info = {
    "Emergency Number Information",
};

const uint8_field hf_emergency_number_length = {
    "Emergency Number Info length",
    0x0,
};

const bool_field hf_police = {
    "Police",
    0x01,
};

const bool_field hf_ambulance = {
    "Ambulance",
    0x02,
};

const bool_field hf_fire_brigade = {
    "Fire Brigade",
    0x04,
};

const bool_field hf_marine_guard = {
    "Marine Guard",
    0x08,
};

const bool_field hf_mountain_rescue = {
    "Mountain Rescue",
    0x10,
};

const bcd_field hf_emergency_bcd_num = {
    "Emergency BCD Number",
};


// Emergency number list  9.11.3.23
int mm::dissect_emergency_number_list(dissector d, context* ctx) {
    const use_context uc(ctx, "emergency-number-list", d, 0);

    // See subclause 10.5.3.13 in 3GPP TS 24.008 [12].

    const auto len = d.length;

    while (d.length > 0) {
        /* Length of 1st Emergency Number information note 1) octet 3
         * NOTE 1: The length contains the number of octets used to encode the
         * Emergency Service Category Value and the Number digits.
         */
        auto       elen    = d.uint8();
        const auto subtree = d.add_item(&hf_emergency_number_info, elen+1);
        use_tree   ut(d, subtree);

        (void) d.add_item( &hf_emergency_number_length);
        d.step(1);

        /* 0 0 0 Emergency Service Category Value
         * Table 10.5.135d/3GPP TS 24.008: Service Category information element
         */
        d.add_item(&hf_police);
        d.add_item(&hf_ambulance);
        d.add_item(&hf_fire_brigade);
        d.add_item(&hf_marine_guard);
        d.add_item(&hf_mountain_rescue);
        d.step(1);
        --elen;
        (void) d.add_item( &hf_emergency_bcd_num, elen);

        d.step(elen);
    }
    return len;
}
