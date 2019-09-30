#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


using namespace nas;
using namespace mm;

extern const tag_field hf_pdu_session_id = {
    "PDU session identity 2",
    0x0,
    (const v_string[]){
        {0x00, "No PDU session identity assigned"},
        {0x01, "Reserved"},
        {0x02, "Reserved"},
        {0x03, "Reserved"},
        {0x04, "Reserved"},
        {0x05, "PDU session identity value 5"},
        {0x06, "PDU session identity value 6"},
        {0x07, "PDU session identity value 7"},
        {0x08, "PDU session identity value 8"},
        {0x09, "PDU session identity value 9"},
        {0x0a, "PDU session identity value 10"},
        {0x0b, "PDU session identity value 11"},
        {0x0c, "PDU session identity value 12"},
        {0x0d, "PDU session identity value 13"},
        {0x0e, "PDU session identity value 14"},
        {0x0f, "PDU session identity value 15"},
        {0, nullptr},
    },
};

// PDU session ID 2 9.11.3.41
int mm::dissect_pdu_session_id_set(dissector d, context* ctx) {
    const use_context uc(ctx, "pdu-session-identity2", d, -1);

    // identity value as defined in 3GPP TS 24.007 [11]
    auto v = vstring(hf_pdu_session_id.tags, d.uint8());
    d.set_item(1, v);
    // (void) d.tree->set_item(1, &hf_pdu_session_id);
    return 1;
}

