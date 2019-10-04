#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.22 Identity response  */
result_t de_identity_response(dissector d, context* ctx, identity_response_t* ret) {
    const use_context uc(&d, ctx, "identity-response", 0);
    // UE to AMF
    up_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.22.1.1: IDENTITY RESPONSE message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Identity response message identity	Message type	9.7	M	V	1
    */
    //        Mobile identity	5GS mobile identity	9.11.3.4	M	LV-E	3-n
    de_le_octet(d, ctx, &ret->nmid).step(d);
    return {uc.consumed()};
}