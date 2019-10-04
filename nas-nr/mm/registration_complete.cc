#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.8 Registration complete */
result_t de_registration_complete(dissector                d,
                                  context*                 ctx,
                                  registration_complete_t* ret) {
    const use_context uc(&d, ctx, "registration-complete", 0);
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.8.1.1: REGISTRATION COMPLETE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Registration complete message identity	Message type	9.7	M	V	1
    */

    // 73	SOR transparent container	9.11.3.51	O	TLV-E	20
    de_tle_octet(d, ctx, 0x73, &ret->sor_container).step(d);
    return {d.offset - uc.offset};
}