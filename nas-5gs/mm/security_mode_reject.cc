#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*  8.2.27 Security mode reject */
int mm::dissect_sec_mode_rej(dissector d, context* ctx) {    
    use_context uc(ctx, "security-mode-reject", d, -1);
    // UE to network
    up_link(d.pinfo);

    /* 5GMM cause 9.11.3.2    M    V    1 */
    const auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    return 1;
}
