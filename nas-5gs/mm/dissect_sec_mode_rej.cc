#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

/*  8.2.27 Security mode reject */
int mm::dissect_sec_mode_rej(dissector d, context* ctx) {    
    use_context uc(ctx, "security-mode-reject", d, 0);

    /* 5GMM cause 9.11.3.2    M    V    1 */
    // ELEM_MAND_V(,  DE_NAS_5GS_MM_5GMM_CAUSE,);
    const auto consumed = dissect_elem_v(nullptr, &mm_cause, d, ctx);
    d.step(consumed);

    d.extraneous_data_check(0);
    return uc.length;
}
