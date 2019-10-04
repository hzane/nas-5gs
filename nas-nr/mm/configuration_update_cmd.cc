#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

/* 8.2.19 Configuration update command */
result_t de_configuration_update_command(dissector                       d,
                                         context*                        ctx,
                                         configuration_update_command_t* ret) {
    const use_context uc(&d, ctx, "configuration-update-command", 0);
    // network to UE
    down_link(d.pinfo);

    de_nmm_header(d, ctx, &ret->header).step(d);

    /*
    Table 8.2.19.1.1: CONFIGURATION UPDATE COMMAND message content
    IEI	Information Element	Type/Reference	Presence	Format	Length
        Extended protocol discriminator	Extended protocol discriminator	9.2	M	V	1
        Security header type	Security header type	9.3	M	V	1/2
        Spare half octet	Spare half octet	9.5	M	V	1/2
        Configuration update command message identity	Message type	9.7	M	V	1
    */
    // D-	Configuration update indication	9.11.3.18	O	TV	1
    de_tv_short(d, ctx, 0xd0, &ret->ind).step(d);

    // 77	5G-GUTI	5GS mobile identity	9.11.3.4	O	TLV-E	14
    de_tle_fixed(d, ctx, 0x77, &ret->nguti_nmid).step(d);

    // 54	TAI list	5GS tracking area identity list	9.11.3.9	O	TLV	9-114
    de_tl_octet(d, ctx, 0x54, &ret->taies).step(d);

    // 15	Allowed NSSAI	NSSAI	9.11.3.37	O	TLV	4-74
    de_tl_octet(d, ctx, 0x15, &ret->allowed_nssai).step(d);

    // 27	Service area list	Service area list	9.11.3.49	O	TLV	6-114
    de_tl_octet(d, ctx, 0x27, &ret->service_areas).step(d);

    // 43	Full name for network	9.11.3.35	O	TLV	3-n
    de_tl_octet(d, ctx, 0x43, &ret->full_name).step(d);

    // 45	Short name for network	9.11.3.35	O	TLV	3-n
    de_tl_octet(d, ctx, 0x45, &ret->short_name).step(d);

    // 46	Local time zone	9.11.3.52	O	TV	2
    de_t_uint8(d, ctx, 0x46, &ret->local_time_zone).step(d);

    // 47	Universal time and local time zone	9.11.3.53	O	TV	8
    de_t_fixed(d, ctx, 0x47, &ret->utc).step(d);

    // 49	Network daylight saving time	9.11.3.19	O	TLV	3
    de_tl_uint8(d, ctx, 0x49, &ret->daylight_saving_time).step(d);

    // 79	LADN information	9.11.3.30	O	TLV-E	3-1715
    de_tle_octet(d, ctx, 0x79, &ret->ladn_information).step(d);

    // B-	MICO indication	MICO indication	9.11.3.31	O	TV	1
    de_tv_short(d, ctx, 0xb0, &ret->mico_ind).step(d);

    // 9-	Network slicing indication	9.11.3.36	O	TV	1
    de_tv_short(d, ctx, 0x90, &ret->network_slicing_ind).step(d);

    // 31	Configured NSSAI	9.11.3.37	O	TLV	4-146
    de_tl_octet(d, ctx, 0x31, &ret->configured_nssai).step(d);

    // 11	Rejected NSSAI	9.11.3.46	O	TLV	4-42
    de_tl_octet(d, ctx, 0x11, &ret->rejected_nssai).step(d);

    // 76	Operator-defined access category definitions	9.11.3.38	O	TLV-E	3-n
    de_tle_octet(d, ctx, 0x76, &ret->access_definitions).step(d);

    // F-	SMS indication	9.11.3.50A O TV	1
    de_tv_short(d, ctx, 0xF0, &ret->sms_ind).step(d);

    // Tbd	T3447 value	GPRS timer 3	9.11.2.5	O	TLV	3
    return {uc.consumed()};
}

