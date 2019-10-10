#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 9.11.3.5     5GS network feature support*/
result_t die_nr_network_feature_support(dissector                     d,
                                        context*                      ctx,
                                        nr_network_feature_support_t* ret) {
    const use_context uc(&d, ctx, "nr-network-feature-support", 1);
    auto              o3 = d.uint8(true), o4 = d.uint8(true);

    ret->ims_vops_3gpp  = mask_u8(o3, 0x01);
    ret->ims_vops_n3gpp = mask_u8(o3, 0x02);
    ret->emc            = mask_u8(o3, 0x0c);

    ret->emf     = mask_u8(o3, 0x30u);
    ret->iwk_n26 = mask_u8(o3, 0x40u);
    ret->mpsi    = mask_u8(o3, 0x80u);

    ret->emcn3       = mask_u8(o4, 0x01);
    ret->mcsi        = mask_u8(o4, 0x02);
    ret->restrict_ec = mask_u8(o4, 0x04);
    ret->ncp_ciot    = mask_u8(o4, 0x08);

    ret->n3data      = mask_u8(o4, 0x10);
    ret->nhc_cp_ciot = mask_u8(o4, 0x20);
    ret->nup_ciot    = mask_u8(o4, 0x40);

    // oct 5 is optional

    return {uc.length};
}
