#include "../common/context.hh"
#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*8.2.21 Identity request */
result_t de_identity_request(dissector d, context* ctx, identity_request_t* ret) {
    const use_context uc(&d, ctx, "identity-request", 0);
    // AMF to UE
    down_link(d.pinfo);
    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.21.1.1: IDENTITY REQUEST message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Identity request message identity	Message type	9.7	M	V	1
    */

    // Identity type	5GS identity type	9.11.3.3	M	V	1/2
    de_nibble(d, ctx, &ret->nr_identity_type).step(d);

    // Spare half octet Spare half octet 9.5 M V 1 / 2;
    return {uc.consumed()};
}