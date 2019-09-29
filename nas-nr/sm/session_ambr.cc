#include "../common/dissect_sm_msg.hh"
#include "../common/use_context.hh"

inline const ambr_field hf_session_ambr_downlink = {
    "Session-AMBR for downlink",
};

inline const ambr_field hf_session_ambr_uplink = {
    "Session-AMBR for uplink",
};

// 9.11.4.14    Session-AMBR
int sm::dissect_session_ambr(dissector d, context* ctx) {
    const use_context uc(ctx, "session-ambr", d, 0);

    /* Unit for Session-AMBR for downlink octet 3*/
    /* Session-AMBR for downlink (octets 4 and 5) */

    (void) d.add_item(&hf_session_ambr_downlink);
    d.step(3);

    (void) d.add_item(&hf_session_ambr_uplink);
    d.step(3);

    return uc.length;
}

