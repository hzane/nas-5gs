#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.12 De-registration request (UE originating de-registration)  */
result_t de_deregistration_request_ue_orig(dissector                         d,
                                           context*                          ctx,
                                           deregistration_request_ue_orig_t* ret) {
    const use_context uc(&d, ctx, "deregistration-request-ue-orig", 0);
    // UE to network
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.12.1.1: DEREGISTRATION REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        De-registration request message identity	Message type	9.7	M	V	1
    */

    // De-registration type	De-registration type	9.11.3.20	M	V	1/2
    de_nibble(d, ctx, &ret->type);

    // ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    de_nibble(d, ctx, &ret->nksi).step(d);

    // 5GS mobile identity		5GS mobile identity	9.11.3.4	M	LV-E	6-n
    de_le_octet(d, ctx, &ret->nmid);
    return {uc.consumed()};
}