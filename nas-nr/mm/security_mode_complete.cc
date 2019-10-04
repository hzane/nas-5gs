#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"
#include "../common/ber.hh"

/*  8.2.26 Security mode complete */
result_t de_security_mode_complete(dissector                 d,
                                   context*                  ctx,
                                   security_mode_complete_t* ret) {
    const use_context uc(&d, ctx, "security-mode-complete", 0);
    // UE to network
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.26.1.1: SECURITY MODE COMPLETE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Security mode complete message identity	Message type	9.6	M	V	1
    */
    // 77	IMEISV	5G mobile identity	9.11.3.4	O	TLV-E	12
    de_tle_fixed(d, ctx, 0x77, &ret->imeisv_nmid).step(d);

    // 71	NAS message container	9.11.3.33	O	TLV-E	4-n
    de_tle(d, ctx, 0x71, &ret->message, de_nas_plain).step(d);
    return {uc.consumed()};
}
