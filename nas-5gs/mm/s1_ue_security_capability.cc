#include "../dissect_mm_msg.hh"

/* 9.11.3.54    UE security capability*/
int mm::dissect_ue_security_capability(dissector d, context* ctx) {
    const use_context uc(ctx, "ue-security-capability", d, 4);

    static const field_meta* oct3_flags[] = {
        &hf_nas_5gs_mm_5g_ea0,
        &hf_nas_5gs_mm_5g_ea1, // 128-
        &hf_nas_5gs_mm_5g_ea2, // 128-
        &hf_nas_5gs_mm_5g_ea3, // 128-
        &hf_nas_5gs_mm_5g_ea4,
        &hf_nas_5gs_mm_5g_ea5,
        &hf_nas_5gs_mm_5g_ea6,
        &hf_nas_5gs_mm_5g_ea7,
        nullptr,
    };

    static const field_meta* oct4_flags[] = {
        &hf_nas_5gs_mm_5g_ia0,
        &hf_nas_5gs_mm_5g_ia1, // 128-
        &hf_nas_5gs_mm_5g_ia2, // 128-
        &hf_nas_5gs_mm_5g_ia3, // 128-
        &hf_nas_5gs_mm_5g_ia4,
        &hf_nas_5gs_mm_5g_ia5,
        &hf_nas_5gs_mm_5g_ia6,
        &hf_nas_5gs_mm_5g_ia7,
        nullptr,
    };

    static const field_meta* oct5_flags[] = {
        &hf_nas_5gs_mm_eea0,
        &hf_nas_5gs_mm_eea1, // 128-
        &hf_nas_5gs_mm_eea2, // 128-
        &hf_nas_5gs_mm_eea3, // 128-
        &hf_nas_5gs_mm_eea4,
        &hf_nas_5gs_mm_eea5,
        &hf_nas_5gs_mm_eea6,
        &hf_nas_5gs_mm_eea7,
        nullptr,
    };

    static const field_meta* oct6_flags[] = {
        &hf_nas_5gs_mm_eia0,
        &hf_nas_5gs_mm_eia1, // 128-
        &hf_nas_5gs_mm_eia2, // 128-
        &hf_nas_5gs_mm_eia3, // 128-
        &hf_nas_5gs_mm_eia4,
        &hf_nas_5gs_mm_eia5,
        &hf_nas_5gs_mm_eia6,
        &hf_nas_5gs_mm_eia7,
        nullptr,
    };

    /* 5G-EA0    128-5G-EA1    128-5G-EA2    128-5G-EA3    5G-EA4    5G-EA5    5G-EA6
     * 5G-EA7    octet 3 */
    d.add_bits(oct3_flags);
    d.step(1);

    /* 5G-IA0    128-5G-IA1    128-5G-IA2    128-5G-IA3    5G-IA4    5G-IA5    5G-IA6
     * 5G-IA7 octet 4 */
    d.add_bits(oct4_flags);
    d.step(1);

    if (d.length < -0) {
        return 2;
    }

    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 octet 5 */
    d.add_bits(oct5_flags);
    d.step(1);

    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 octet 6 */
    d.add_bits(oct6_flags);
    d.step(1);

    if (d.length <= 0) return 4;

    // 7-10 is spare

    return 4 + d.length;
}

/*  9.11.3.54    UE security capability  */
int mm::dissect_replayed_ue_sec_cap(dissector d, context* ctx) {
    const use_context uc(ctx, "ue-security-capability", d, 0);    

    static const field_meta* oct3_flags[] = {
        &hf_mm_5g_ea0,
        &hf_mm_128_5g_ea1,
        &hf_mm_128_5g_ea2,
        &hf_mm_128_5g_ea3,
        &hf_mm_5g_ea4,
        &hf_mm_5g_ea5,
        &hf_mm_5g_ea6,
        &hf_mm_5g_ea7,
        nullptr,
    };

    static const field_meta* oct4_flags[] = {
        &hf_mm_5g_ia0,
        &hf_mm_128_5g_ia1,
        &hf_mm_128_5g_ia2,
        &hf_mm_128_5g_ia3,
        &hf_mm_5g_ia4,
        &hf_mm_5g_ia5,
        &hf_mm_5g_ia6,
        &hf_mm_5g_ia7,
        nullptr,
    };

    static const field_meta* oct5_flags[] = {
        &hf_mm_eea0,
        &hf_mm_128eea1,
        &hf_mm_128eea2,
        &hf_mm_eea3,
        &hf_mm_eea4,
        &hf_mm_eea5,
        &hf_mm_eea6,
        &hf_mm_eea7,
        nullptr,
    };

    static const field_meta* oct6_flags[] = {
        &hf_mm_eia0,
        &hf_mm_128eia1,
        &hf_mm_128eia2,
        &hf_mm_eia3,
        &hf_mm_eia4,
        &hf_mm_eia5,
        &hf_mm_eia6,
        &hf_mm_eia7,
        nullptr,
    };

    /* 5G-EA0    128-5G-EA1    128-5G-EA2    128-5G-EA3    5G-EA4    5G-EA5    5G-EA6
     * 5G-EA7    octet 3 */
    d.add_bits(oct3_flags);
    d.step(1);

    /* 5G-IA0    128-5G-IA1    128-5G-IA2    128-5G-IA3    5G-IA4    5G-IA5    5G-IA6
     * 5G-IA7 octet 4 */
    d.add_bits(oct4_flags);
    d.step(1);

    if (uc.length == 2) {
        return 2;
    }

    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 octet 5 */
    d.add_bits(oct5_flags);
    d.step(1);

    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 octet 6 */
    d.add_bits(oct6_flags);
    d.step(1);

    return uc.length;
}
