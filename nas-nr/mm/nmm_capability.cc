#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// 9.11.3.1	5GMM capability
result_t die_nmm_capability(dissector d, context* ctx, nmm_capability_t* ret) {
    const use_context uc(&d, ctx, "nmm-capability", 11);
    auto              o3 = d.uint8(true);
    ret->s1_mode         = mask_u8(o3, 0x01);
    ret->ho_attach       = mask_u8(o3, 0x02);
    ret->lpp             = mask_u8(o3, 0x04);
    ret->restrict_ec     = mask_u8(o3, 0x08);
    ret->ncp_ciot        = mask_u8(o3, 0x10);
    ret->n3data          = mask_u8(o3, 0x20);
    ret->nhccp_ciot      = mask_u8(o3, 0x40);
    ret->sgc             = mask_u8(o3, 0x80u);

    if (d.length > 0) {
        auto o4       = d.uint8(true);
        ret->nsrvcc   = mask_u8(o4, 0x01);
        ret->nup_ciot = mask_u8(o4, 0x02);
    }

    // 5-15 octets is spare
    return {uc.length};
}
