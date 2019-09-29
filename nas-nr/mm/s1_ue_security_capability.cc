#include <utility>

#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"


static const char* supported = "Supported";
static const char* notsupported = "Not supported";

// S1 UE network capability 9.11.3.48
const bool_field hf_nas_eps_emm_ucs2_supp = {
    "UCS2 support (UCS2)",
    0x80,
    "The UE has a preference for the default alphabet",
    "The UE has no preference between the use of the default alphabet and the use of "
    "UCS2",
};

const bool_field nrea0={    "5G-EA0",    0x80u, notsupported,supported};
const bool_field nrea1={    "128-5G-EA1",    0x40u, notsupported,supported};
const bool_field nrea2={    "128-5G-EA2",    0x20u, notsupported,supported};
const bool_field nrea3={    "128-5G-EA3",    0x10u, notsupported,supported};
const bool_field nrea4={    "5G-EA4",    0x08u, notsupported,supported};
const bool_field nrea5={    "5G-EA5",    0x04u, notsupported,supported};
const bool_field nrea6={    "5G-EA6",    0x02u, notsupported,supported};
const bool_field nrea7={    "5G-EA7",    0x01u, notsupported,supported};


const bool_field nria0={    "5G-IA0",    0x80u, notsupported,supported};
const bool_field nria1={    "128-5G-IA1",    0x40u, notsupported,supported};
const bool_field nria2={    "128-5G-IA2",    0x20u, notsupported,supported};
const bool_field nria3={    "128-5G-IA3",    0x10u, notsupported,supported};
const bool_field nria4={    "5G-IA4",    0x08u, notsupported,supported};
const bool_field nria5={    "5G-IA5",    0x04u, notsupported,supported};
const bool_field nria6={    "5G-IA6",    0x02u, notsupported,supported};
const bool_field nria7={    "5G-IA7",    0x01u, notsupported,supported};

const bool_field eea0={    "EEA0",    0x80u, notsupported,supported};
const bool_field eea1={    "128-EIA1",    0x40u, notsupported,supported};
const bool_field eea2={    "128-EIA2",    0x20u, notsupported,supported};
const bool_field eea3={    "128-EIA3",    0x10u, notsupported,supported};
const bool_field eea4={    "EEA4",    0x08u, notsupported,supported};
const bool_field eea5={    "EEA5",    0x04u, notsupported,supported};
const bool_field eea6={    "EEA6",    0x02u, notsupported,supported};
const bool_field eea7={    "EEA7",    0x01u, notsupported,supported};

const bool_field eia0={    "EIA0",    0x80u, notsupported,supported};
const bool_field eia1={    "128-EIA1",    0x40u, notsupported,supported};
const bool_field eia2={    "128-EIA2",    0x20u, notsupported,supported};
const bool_field eia3={    "128-EIA3",    0x10u, notsupported,supported};
const bool_field eia4={    "EIA4",    0x08u, notsupported,supported};
const bool_field eia5={    "EIA5",    0x04u, notsupported,supported};
const bool_field eia6={    "EIA6",    0x02u, notsupported,supported};
const bool_field eia7={    "EIA7",    0x01u, notsupported,supported};

/* 9.11.3.54    UE security capability*/
int mm::dissect_ue_security_capability(dissector d, context* ctx) {
    const use_context uc(ctx, "ue-security-capability", d, 4);

    static const bool_field* oct3_flags[] = {
        &nrea0,
        &nrea1, // 128-
        &nrea2, // 128-
        &nrea3, // 128-
        &nrea4,
        &nrea5,
        &nrea6,
        &nrea7,
        nullptr,
    };

    static const bool_field* oct4_flags[] = {
        &nria0,
        &nria1,     // 128-
        &nria2, // 128-
        &nria3, // 128-
        &nria4,
        &nria5,
        &nria6,
        &nria7,
        nullptr,
    };

    static const bool_field* oct5_flags[] = {
        &eea0,
        &eea1, // 128-
        &eea2, // 128-
        &eea3, // 128-
        &eea4,
        &eea5,
        &eea6,
        &eea7,
        nullptr,
    };

    static const bool_field* oct6_flags[] = {
        &eia0,
        &eia1, // 128-
        &eia2, // 128-
        &eia3, // 128-
        &eia4,
        &eia5,
        &eia6,
        &eia7,
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

    if (d.length <= 0) {
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
int mm::dissect_replayed_ue_security_capability(dissector d, context* ctx) {
    return dissect_ue_security_capability(std::move(d), ctx);
}
