#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

const bool_field ksi_tsc_flag = {
    "Type of security context flag (TSC)",
    0x08,
    "Native security context (for KSIAMF)",
    "Mapped security context (for KSIASME)",
};

/* NAS key set identifier (octet 1) Bits 3  2   1 */

const tag_field hf_eps_nas_ksi = { // NOLINT
    "NAS key set identifier",
    0x07,
    (const v_string[]){
        {0, "0"},
        {1, "1"},
        {2, "2"},
        {3, "3"},
        {4, "4"},
        {5, "5"},
        {6, "6"},
        {7, "No key is available"},
        {0, nullptr},
    },
};
// 9.11.3.32	NAS key set identifier
int mm::dissect_nas_ksi(dissector d, context* ctx) {
    use_context uc(ctx, "NAS key set identifier", d, -1);

    /* NAS key set identifier IEI   TSC     NAS key set identifier */
    d.add_item(&ksi_tsc_flag);
    d.add_item(&hf_eps_nas_ksi);

    d.step(1);

    return 1;
}


