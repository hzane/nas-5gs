#include "common.hh"
#include "../common/use_context.hh"

const bool_field s1_tsc_flag = {
    "Type of security context flag (TSC)",
    0x08,
    "Native security context (for KSIAMF)",
    "Mapped security context (for KSIASME)",
};

int cmn::dissect_s1_to_n1_mode_container(dissector d, context* ctx) {
    const use_context uc(ctx, "s1-mode-to-n1-mode-transparent-container", d, 2);

    /*The value part of the Intra N1 mode NAS transparent container information element is
included in specific information elements within some RRC messages sent to the UE.*/
    d.add_item(&hf_authentication_code, 4, false);
    d.step(4);

    d.add_item(&hf_integrity_algo_type, false);
    d.add_item(&hf_ciphering_algo_type, false);
    d.step(1);

    (void) d.add_item(&hf_ksi_5g);
    (void) d.add_item(&s1_tsc_flag);
    (void) d.add_item(&hf_next_hop_chaining_counter);
    d.step(1);

    // oct 9-10 is spare
    d.step(2);

    return uc.length;
}

// Next hop chaining counter (see 3GPP TS 33.501 [24])
extern const uint8_field hf_next_hop_chaining_counter = {
    "Next hop chaining counter (NCC)",
    0x70u,
};

