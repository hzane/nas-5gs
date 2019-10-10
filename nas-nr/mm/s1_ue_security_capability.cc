#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

/* 9.11.3.54    UE security capability*/
result_t die_ue_security_capability(dissector                 d,
                                    context*                  ctx,
                                    ue_security_capability_t* ret) {
    const use_context uc(&d, ctx, "ue-security-capability", 4);
    ret->nea = d.uint8(true);
    ret->nia = d.uint8(true);
    if (d.length>0){
        ret->eea.present = true;
        ret->eea.v       = d.uint8(true);
        ret->eia.present = true;
        ret->eia.v       = d.uint8(true);
    }
    return {uc.length};
}
