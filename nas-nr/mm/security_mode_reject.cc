#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.27 Security mode reject */
result_t de_security_mode_reject(dissector d, context* ctx, security_mode_reject_t* ret) {
    const use_context uc(&d, ctx, "security-mode-reject", 0);
    // UE to network
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.27.1.1: SECURITY MODE REJECT message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Security mode reject message identity	Message type	9.6	M	V	1
    */
    //        5GMM cause	5GMM cause	9.11.3.2	M	V	1
    de_uint8(d, ctx, &ret->cause).step(d);

    return {uc.consumed()};
}