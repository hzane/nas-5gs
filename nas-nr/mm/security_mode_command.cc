#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.25 Security mode command  */
result_t de_security_mode_command(dissector                d,
                                  context*                 ctx,
                                  security_mode_command_t* ret) {
    const use_context uc(&d, ctx, "security-mode-command", 0);
    /* Direction: network to UE */
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);
    /*
    Table 8.2.25.1.1: SECURITY MODE COMMAND message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Security mode command message identity	Message type	9.7	M	V	1
    */
    // Selected NAS security algorithms		9.11.3.34	M	V	1
    de_uint8(d, ctx, &ret->selected_security_algo).step(d);

    // ngKSI	NAS key set identifier	9.11.3.32	M	V	1/2
    // Spare half octet	Spare half octet	9.5	M	V	1/2
    de_nibble(d, ctx, &ret->nksi).step(d);

    // Replayed UE security capabilities	9.11.3.54	M LV 3-9
    de_l_octet(d, ctx, &ret->replayed_ue_security_capabilities).step(d);

    // E-	IMEISV request	IMEISV request	9.11.3.28	O	TV	1
    de_tv_short(d, ctx, 0xe0, &ret->imeisv_request).step(d);

    // 57	Selected EPS NAS   security algorithms 9.11.3.25 O	TV	2
    de_t_uint8(d, ctx, 0x57, &ret->selected_eps_security_algo).step(d);

    // 36	Additional 5G security  information	9.11.3.12	O	TLV	3
    de_tl_uint8(d, ctx, 0x36, &ret->additional_5g_security_information).step(d);

    // 78	EAP message	EAP message	9.11.2.2	O	TLV-E    7-1503
    de_tle_octet(d, ctx, 0x78, &ret->eap).step(d);

    // 38	ABBA	ABBA	9.11.3.10	O	TLV	4-n
    de_tl_octet(d, ctx, 0x38, &ret->abba).step(d);

    // 19	Replayed S1 UE security    capability	9.11.3.48A	O	TLV	4-7
    de_tl_octet(d, ctx, 0x19, &ret->replayed_s1_ue_security_capabilities).step(d);
    return {uc.consumed()};
}