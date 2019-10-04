#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.29 5GMM status */
result_t de_nmm_status(dissector d, context* ctx, nmm_status_t* ret) {
    const use_context uc(&d, ctx, "security-mode-reject", 0);
    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.29.1.1: 5GMM STATUS message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        5GMM STATUS message identity	Message type	9.7	M	V	1
    */
    //        5GMM cause	5GMM cause	9.11.3.2	M	V	1
    de_uint8(d, ctx, &ret->nmm_cause).step(d);

    return {uc.consumed()};
}