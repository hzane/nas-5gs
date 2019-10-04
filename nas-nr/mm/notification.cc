#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/*  8.2.23 Notification */
result_t de_notification(dissector d, context* ctx, notification_t* ret) {
    const use_context uc(&d, ctx, "notification", 0);
    // network to UE
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.23.1.1: NOTIFICATION message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Notification message identity	Message type	9.7	M	V	1
    */
    // Access type	Access type	9.11.3.11	M	V	1/2
    de_nibble(d, ctx, &ret->access_type).step(d);
    // Spare half octet	Spare half octet	9.5	M	V	1/2
    return {uc.consumed()};
}