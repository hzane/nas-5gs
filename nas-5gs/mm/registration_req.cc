#include "../dissect_mm_msg.hh"
#include "../gsm.hh"
#include "../ts24007.hh"
#include "5gs_registration.hh"

using namespace cmn;
using namespace mm;
using namespace nas;


namespace mm{

} // namespace mm



namespace mm {
const true_false_string tfs_supp_or_not = {
    "Supported",
    "Not supported",
};

const field_meta hf_nas_5gs_mm_5g_ea0 = {
    "5G-EA0",
    "nas_5gs.mm.5g_ea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_5g_ea1 = {
    "128-5G-EA1",
    "nas_5gs.mm.128_5g_ea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_5g_ea2 = {
    "128-5G-EA2",
    "nas_5gs.mm.128_5g_ea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_5g_ea3 = {
    "128-5G-EA3",
    "nas_5gs.mm.128_5g_ea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_5g_ea4 = {
    "5G-EA4",
    "nas_5gs.mm.5g_ea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_5g_ea5 = {
    "5G-EA5",
    "nas_5gs.mm.5g_ea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_5g_ea6 = {
    "5G-EA6",
    "nas_5gs.mm.5g_ea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_5g_ea7 = {
    "5G-EA7",
    "nas_5gs.mm.5g_ea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_mm_5g_ia0 = {
    "5G-IA0",
    "nas_5gs.mm.ia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_5g_ia1 = {
    "128-5G-IA1",
    "nas_5gs.mm.5g_128_ia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_5g_ia2 = {
    "128-5G-IA2",
    "nas_5gs.mm.5g_128_ia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_5g_ia3 = {
    "128-5G-IA3",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_5g_ia4 = {
    "5G-IA4",
    "nas_5gs.mm.5g_128_ia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_5g_ia5 = {
    "5G-IA5",
    "nas_5gs.mm.5g_ia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_5g_ia6 = {
    "5G-IA6",
    "nas_5gs.mm.5g_ia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_5g_ia7 = {
    "5G-IA7",
    "nas_5gs.mm.5g_ia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_mm_eea0 = {
    "EEA0",
    "nas_5gs.mm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_eea1 = {
    "128-EEA1",
    "nas_5gs.mm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_eea2 = {
    "128-EEA2",
    "nas_5gs.mm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_eea3 = {
    "128-EEA3",
    "nas_5gs.mm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_eea4 = {
    "EEA4",
    "nas_5gs.mm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_eea5 = {
    "EEA5",
    "nas_5gs.mm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_eea6 = {
    "EEA6",
    "nas_5gs.mm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_eea7 = {
    "EEA7",
    "nas_5gs.mm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_mm_eia0 = {
    "EIA0",
    "nas_5gs.mm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_mm_eia1 = {
    "128-EIA1",
    "nas_5gs.mm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_mm_eia2 = {
    "128-EIA2",
    "nas_5gs.mm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_mm_eia3 = {
    "128-EIA3",
    "nas_5gs.mm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_mm_eia4 = {
    "EIA4",
    "nas_5gs.mm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_mm_eia5 = {
    "EIA5",
    "nas_5gs.mm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_mm_eia6 = {
    "EIA6",
    "nas_5gs.mm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_mm_eia7 = {
    "EIA7",
    "nas_5gs.mm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};
} // namespace mm

/* 9.11.3.54    UE security capability*/
int mm::dissect_use_sec_cap(dissector d, context* ctx) {
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

    if (d.length<-0) {
        return 2;
    }

    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 octet 5 */
    d.add_bits( oct5_flags);
    d.step(1);

    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 octet 6 */
    d.add_bits(oct6_flags);
    d.step(1);

    if (d.length <= 0) return 4;

    // 7-10 is spare

    return 4 + d.length;
}

//* 9.11.3.8     5GS tracking area identity
int mm::dissect_last_v_tai(dissector d, context* ctx) {
    /* MCC digit 2    MCC digit 1 Octet 2*/
    /* MNC digit 3    MCC digit 3 Octet 3*/
    /* MNC digit 2    MNC digit 1 Octet 4*/
   dissect_e212_mcc_mnc(d, ctx);
   d.step(3);

    /* TAC Octet 5 - 7 */
   d.add_item(3, &hf_tac, enc::na);
   return 6;
}

namespace mm {
// S1 UE network capability 9.11.3.48
const true_false_string nas_eps_emm_ucs2_supp_flg_value = {
    "The UE has no preference between the use of the default alphabet and the use of "
    "UCS2",
    "The UE has a preference for the default alphabet",
};

const field_meta hf_nas_eps_emm_eea0 = {
    "EEA0",
    "nas_eps.emm.eea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};

const field_meta hf_nas_eps_emm_128eea1 = {
    "128-EEA1",
    "nas_eps.emm.128eea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};

const field_meta hf_nas_eps_emm_128eea2 = {
    "128-EEA2",
    "nas_eps.emm.128eea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};

const field_meta hf_nas_eps_emm_eea3 = {
    "128-EEA3",
    "nas_eps.emm.eea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_eea4 = {
    "EEA4",
    "nas_eps.emm.eea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_eea5 = {
    "EEA5",
    "nas_eps.emm.eea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_eea6 = {
    "EEA6",
    "nas_eps.emm.eea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_eea7 = {
    "EEA7",
    "nas_eps.emm.eea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_eia0 = {
    "EIA0",
    "nas_eps.emm.eia0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_128eia1 = {
    "128-EIA1",
    "nas_eps.emm.128eia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_128eia2 = {
    "128-EIA2",
    "nas_eps.emm.128eia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_eia3 = {
    "128-EIA3",
    "nas_eps.emm.eia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_eia4 = {
    "EIA4",
    "nas_eps.emm.eia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_eia5 = {
    "EIA5",
    "nas_eps.emm.eia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_eia6 = {
    "EIA6",
    "nas_eps.emm.eia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_eia7 = {
    "EIA7",
    "nas_eps.emm.eia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_uea0 = {
    "UEA0",
    "nas_eps.emm.uea0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_uea1 = {
    "UEA1",
    "nas_eps.emm.uea1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_uea2 = {
    "UEA2",
    "nas_eps.emm.uea2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_uea3 = {
    "UEA3",
    "nas_eps.emm.uea3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_uea4 = {
    "UEA4",
    "nas_eps.emm.uea4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_uea5 = {
    "UEA5",
    "nas_eps.emm.uea5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_uea6 = {
    "UEA6",
    "nas_eps.emm.uea6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_uea7 = {
    "UEA7",
    "nas_eps.emm.uea7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_ucs2_supp = {
    "UCS2 support (UCS2)",
    "nas_eps.emm.emm_ucs2_supp",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_eps_emm_ucs2_supp_flg_value,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_uia1 = {
    "UMTS integrity algorithm UIA1",
    "nas_eps.emm.uia1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_uia2 = {
    "UMTS integrity algorithm UIA2",
    "nas_eps.emm.uia2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_uia3 = {
    "UMTS integrity algorithm UIA3",
    "nas_eps.emm.uia3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_uia4 = {
    "UMTS integrity algorithm UIA4",
    "nas_eps.emm.uia4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_uia5 = {
    "UMTS integrity algorithm UIA5",
    "nas_eps.emm.uia5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_uia6 = {
    "UMTS integrity algorithm UIA6",
    "nas_eps.emm.uia6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_uia7 = {
    "UMTS integrity algorithm UIA7",
    "nas_eps.emm.uia7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_prose_dd_cap = {
    "ProSe direct discovery",
    "nas_eps.emm.prose_dd_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_prose_cap = {
    "ProSe",
    "nas_eps.emm.prose_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_h245_ash_cap = {
    "H.245 After SRVCC Handover",
    "nas_eps.emm.h245_ash_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_acc_csfb_cap = {
    "Access class control for CSFB",
    "nas_eps.emm.acc_csfb_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_lpp_cap = {
    "LTE Positioning Protocol",
    "nas_eps.emm.lpp_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_lcs_cap = {
    "Location services (LCS) notification mechanisms",
    "nas_eps.emm.lcs_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_1xsrvcc_cap = {
    "SRVCC from E-UTRAN to cdma2000 1xCS",
    "nas_eps.emm.1xsrvcc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_nf_cap = {
    "Notification procedure",
    "nas_eps.emm.nf_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_emm_epco_cap = {
    "Extended protocol configuration options",
    "nas_eps.emm.epco_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_emm_hc_cp_ciot_cap = {
    "Header compression for control plane CIoT EPS optimization",
    "nas_eps.emm.hc_cp_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_emm_er_wo_pdn_cap = {
    "EMM-REGISTERED w/o PDN connectivity",
    "nas_eps.emm.er_wo_pdn_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_emm_s1u_data_cap = {
    "S1-U data transfer",
    "nas_eps.emm.s1u_data_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_emm_up_ciot_cap = {
    "User plane CIoT EPS optimization",
    "nas_eps.emm.up_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_emm_cp_ciot_cap = {
    "Control plane CIoT EPS optimization",
    "nas_eps.emm.cp_ciot_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_emm_prose_relay_cap = {
    "ProSe UE-to-network relay",
    "nas_eps.emm.prose_relay_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_emm_prose_dc_cap = {
    "ProSe direct communication",
    "nas_eps.emm.prose_dc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_15_bearers_cap = {
    "Signalling for a maximum number of 15 EPS bearer contexts",
    "nas_eps.emm.15_bearers_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x80,
};
const field_meta hf_nas_eps_sgc_cap = {
    "Service gap control",
    "nas_eps.emm.sgc_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x40,
};
const field_meta hf_nas_eps_n1mode_cap = {
    "N1 mode",
    "nas_eps.emm.n1mode_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x20,
};
const field_meta hf_nas_eps_dcnr_cap = {
    "Dual connectivity with NR",
    "nas_eps.emm.dcnr_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x10,
};
const field_meta hf_nas_eps_cp_backoff_cap = {
    "Control plane data backoff",
    "nas_eps.emm.cp_backoff_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x08,
};
const field_meta hf_nas_eps_restrict_ec_cap = {
    "Restriction on use of enhanced coverage",
    "nas_eps.emm.restrict_ec_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x04,
};
const field_meta hf_nas_eps_v2x_pc5_cap = {
    "V2X communication over PC5",
    "nas_eps.emm.v2x_pc5_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x02,
};
const field_meta hf_nas_eps_multiple_drb_cap = {
    "Multiple DRB",
    "nas_eps.emm.multiple_drb_cap",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_supp_or_not,
    nullptr,
    0x01,
};

const field_meta hf_nas_eps_spare_bits = {
    "Spare bit(s)",
    "nas_eps.spare_bits",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
} // namespace mm

// 9.11.3.48 S1 UE network capability page.391
// See subclause 9.9.3.34 in 3GPP TS 24.301 [15].
int mm::dissect_s1_ue_net_cap(dissector d, context* ctx) {
    static const field_meta* oct3_flags[] = {
        &hf_nas_eps_emm_eea0,
        &hf_nas_eps_emm_128eea1,
        &hf_nas_eps_emm_128eea2,
        &hf_nas_eps_emm_eea3,
        &hf_nas_eps_emm_eea4,
        &hf_nas_eps_emm_eea5,
        &hf_nas_eps_emm_eea6,
        &hf_nas_eps_emm_eea7,
        nullptr,
    };

    static const field_meta* oct4_flags[] = {
        &hf_nas_eps_emm_eia0,
        &hf_nas_eps_emm_128eia1,
        &hf_nas_eps_emm_128eia2,
        &hf_nas_eps_emm_eia3,
        &hf_nas_eps_emm_eia4,
        &hf_nas_eps_emm_eia5,
        &hf_nas_eps_emm_eia6,
        &hf_nas_eps_emm_eia7,
        nullptr,
    };

    static const field_meta* oct5_flags[] = {
        &hf_nas_eps_emm_uea0,
        &hf_nas_eps_emm_uea1,
        &hf_nas_eps_emm_uea2,
        &hf_nas_eps_emm_uea3,
        &hf_nas_eps_emm_uea4,
        &hf_nas_eps_emm_uea5,
        &hf_nas_eps_emm_uea6,
        &hf_nas_eps_emm_uea7,
        nullptr,
    };

    static const field_meta* oct6_flags[] = {
        &hf_nas_eps_emm_ucs2_supp,
        &hf_nas_eps_emm_uia1,
        &hf_nas_eps_emm_uia2,
        &hf_nas_eps_emm_uia3,
        &hf_nas_eps_emm_uia4,
        &hf_nas_eps_emm_uia5,
        &hf_nas_eps_emm_uia6,
        &hf_nas_eps_emm_uia7,
        nullptr,
    };

    static const field_meta* oct7_flags[] = {
        &hf_nas_eps_emm_prose_dd_cap,
        &hf_nas_eps_emm_prose_cap,
        &hf_nas_eps_emm_h245_ash_cap,
        &hf_nas_eps_emm_acc_csfb_cap,
        &hf_nas_eps_emm_lpp_cap,
        &hf_nas_eps_emm_lcs_cap,
        &hf_nas_eps_emm_1xsrvcc_cap,
        &hf_nas_eps_emm_nf_cap,
        nullptr,
    };

    static const field_meta* oct8_flags[] = {
        &hf_nas_eps_emm_epco_cap,
        &hf_nas_eps_emm_hc_cp_ciot_cap,
        &hf_nas_eps_emm_er_wo_pdn_cap,
        &hf_nas_eps_emm_s1u_data_cap,
        &hf_nas_eps_emm_up_ciot_cap,
        &hf_nas_eps_emm_cp_ciot_cap,
        &hf_nas_eps_emm_prose_relay_cap,
        &hf_nas_eps_emm_prose_dc_cap,
        nullptr,
    };

    static const field_meta* oct9_flags[] = {
        &hf_nas_eps_15_bearers_cap,
        &hf_nas_eps_sgc_cap,
        &hf_nas_eps_n1mode_cap,
        &hf_nas_eps_dcnr_cap,
        &hf_nas_eps_cp_backoff_cap,
        &hf_nas_eps_restrict_ec_cap,
        &hf_nas_eps_v2x_pc5_cap,
        &hf_nas_eps_multiple_drb_cap,
        nullptr,
    };
    auto len = d.length;

    /* EPS encryption algorithms supported (octet 3) */
    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 */
    d.add_bits(oct3_flags);
    d.step(1);

    /* EPS integrity algorithms supported (octet 4) */
    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 */
    d.add_bits(oct4_flags);
    d.step(1);

    /* Following octets are optional */
    if(d.length<=0) return 2;

    /* UMTS encryption algorithms supported (octet 5)
     * UEA0    UEA1    UEA2    UEA3    UEA4    UEA5    UEA6    UEA7 */
    d.add_bits(oct5_flags);
    d.step(1);

    if (d.length <= 0) return 3;

    /* Octet 6 */
    /* UCS2    UIA1    UIA2    UIA3    UIA4    UIA5    UIA6    UIA7 */
    d.add_bits(oct6_flags);
    d.step(1);

    if (d.length <= 0) return 4;

    /* Octet 7
     * ProSe-dd ProSe    H.245-ASH    ACC-CSFB    LPP    LCS    1xSR VCC    NF
     */
    d.add_bits(oct7_flags);
    d.step(1);

    if (d.length <= 0) return len;

    /* Octet 8
     * ePCO    HC-CP CIoT    ERw/oPDN    S1-U data    UP CIoT    CP CIoT    Prose-relay
     * ProSe-dc
     */
    d.add_bits(oct8_flags );
    d.step(1);

    if (d.length <= 0) return len;

    /* Octet 9
     * 0 Spare    SGC    N1mode    DCNR    CP backoff    RestrictEC    V2X PC5 multipleDRB
     */
    // hf_nas_eps_spare_bits
    d.add_bits(oct9_flags);
    d.step(1);

    while (d.length >= 0) {
        d.add_item(1, &hf_nas_eps_spare_bits, enc::be);
        d.step(1);
    }
    return len;
}
/*
 * 9.11.3.57    Uplink data status
 */
const true_false_string tfs_nas_5gs_ul_data_sts_psi = {
    "uplink data are pending",
    "no uplink data are pending",
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_7_b7 = {
    "PSI(7)",
    "nas_5gs.ul_data_sts_psi_7_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x80,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_6_b6 = {
    "PSI(6)",
    "nas_5gs.ul_data_sts_psi_6_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x40,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_5_b5 = {
    "PSI(5)",
    "nas_5gs.ul_data_sts_psi_5_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x20,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_4_b4 = {
    "PSI(4)",
    "nas_5gs.ul_data_sts_psi_4_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x10,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_3_b3 = {
    "PSI(3)",
    "nas_5gs.ul_data_sts_psi_3_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x08,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_2_b2 = {
    "PSI(2)",
    "nas_5gs.ul_data_sts_psi_2_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x04,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_1_b1 = {
    "PSI(1)",
    "nas_5gs.ul_data_sts_psi_1_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x02,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_0_b0 = {
    "Spare",
    "nas_5gs.ul_data_sts_psi_0_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
};

const field_meta mm::hf_nas_5gs_ul_data_sts_psi_15_b7 = {
    "PSI(15)",
    "nas_5gs.ul_data_sts_psi_15_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x80,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_14_b6 = {
    "PSI(14)",
    "nas_5gs.ul_data_sts_psi_14_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x40,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_13_b5 = {
    "PSI(13)",
    "nas_5gs.ul_data_sts_psi_13_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x20,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_12_b4 = {
    "PSI(12)",
    "nas_5gs.ul_data_sts_psi_12_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x10,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_11_b3 = {
    "PSI(11)",
    "nas_5gs.ul_data_sts_psi_11_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x08,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_10_b2 = {
    "PSI(10)",
    "nas_5gs.ul_data_sts_psi_10_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x04,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_9_b1 = {
    "PSI(9)",
    "nas_5gs.ul_data_sts_psi_9_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x02,
};
const field_meta mm::hf_nas_5gs_ul_data_sts_psi_8_b0 = {
    "PSI(8)",
    "nas_5gs.ul_data_sts_psi_8_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&tfs_nas_5gs_ul_data_sts_psi,nullptr,
    0x01,
};

/*40    Uplink data status    Uplink data status 9.11.3.57    O    TLV    4-34 */
int mm::dissect_ul_data_status(dissector d, context* ctx) {
    static const field_meta* psi_0_7_flags[] = {
        &hf_nas_5gs_ul_data_sts_psi_7_b7,
        &hf_nas_5gs_ul_data_sts_psi_6_b6,
        &hf_nas_5gs_ul_data_sts_psi_5_b5,
        &hf_nas_5gs_ul_data_sts_psi_4_b4,
        &hf_nas_5gs_ul_data_sts_psi_3_b3,
        &hf_nas_5gs_ul_data_sts_psi_2_b2,
        &hf_nas_5gs_ul_data_sts_psi_1_b1,
        &hf_nas_5gs_ul_data_sts_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_nas_5gs_ul_data_sts_psi_15_b7,
        &hf_nas_5gs_ul_data_sts_psi_14_b6,
        &hf_nas_5gs_ul_data_sts_psi_13_b5,
        &hf_nas_5gs_ul_data_sts_psi_12_b4,
        &hf_nas_5gs_ul_data_sts_psi_11_b3,
        &hf_nas_5gs_ul_data_sts_psi_10_b2,
        &hf_nas_5gs_ul_data_sts_psi_9_b1,
        &hf_nas_5gs_ul_data_sts_psi_8_b0,
        nullptr,
    };

    d.add_bits(psi_0_7_flags);
    d.step(1);

    d.add_bits(psi_8_15_flags);
    d.step(1);

    d.extraneous_data_check(0);

    return 2;
}

/* 6D   UE status UE status 9.9.3.54 O TLV 3 */
/*
 *    9.11.3.56    UE status
 */

const true_false_string tfs_nas_5gs_mm_n1_mod = { // NOLINT
    "UE is in 5GMM-REGISTERED state",
    "UE is not in 5GMM-REGISTERED state",
};

const true_false_string tfs_nas_5gs_mm_s1_mod = { // NOLINT
    "UE is in EMM-REGISTERED state",
    "UE is not in EMM-REGISTERED state",
};
#if 0
const field_meta hf_spare_b6 = {
    "Spare",
    "nas_5gs.spare_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x40,
};
const field_meta hf_spare_b5 = {
    "Spare",
    "nas_5gs.spare_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x20,
};
const field_meta hf_nas_5gs_spare_b4 = {
    "Spare",
    "nas_5gs.spare_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,nullptr,nullptr,
    0x10,
};
#endif

// 9.11.3.56
int mm::dissect_ue_status(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b7,
        &hf_spare_b6,
        &hf_spare_b5,
        &hf_spare_b4,
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_mm_n1_mode_reg_b1,
        &hf_mm_s1_mode_reg_b0,
        nullptr,
    };
    /* 0     0     0     0     0     0     0 Spare    S1  mode reg */
    d.add_bits(flags);
    return 1;
}

// 9.11.3.4
int mm::dissect_aguti_mobile_id(dissector d, context* ctx) {
    return mm::dissect_mobile_id(d, ctx);
}

// 9.11.3.13
int mm::dissect_pdu_ses_sts(dissector d, context* ctx) {
    return mm::dissect_pdu_ses_status(d, ctx);
}

// UE's usage setting    UE's usage setting         9.11.3.55
/*
 * 9.11.3.55    UE's usage setting
 */
static true_false_string tfs_nas_5gs_mm_ue_usage_setting = {
    "Data centric",
    "Voice centric",
};

const field_meta mm::hf_nas_5gs_mm_ue_usage_setting = {
    "UE's usage setting",
    "nas_5gs.mm.ue_usage_setting",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_mm_ue_usage_setting,
    nullptr,
    0x01,
};

// 9.11.3.55
int mm::dissect_usage_set(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_spare_b1,
        &hf_nas_5gs_mm_ue_usage_setting,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

/* 9.11.3.24    EPS NAS message container */
int mm::dissect_eps_nas_msg_cont(dissector d, context* ctx) {
    diag("no eps dissector\n");
    // An EPS NAS message as specified in 3GPP TS 24.301
    return d.length;
}



/*
 * 9.11.3.9A    5GS update type
 */
const true_false_string tfs_nas5gs_sms_requested = { // NOLINT
    "SMS over NAS supported",
    "SMS over NAS not supported",
};
const true_false_string tfs_needed_not_needed = {"Needed", "Not Needed"};
const field_meta        mm::hf_ng_ran_rcu        = {
    "NG-RAN Radio Capability Update (NG-RAN-RCU)",
    "nas_5gs.mm.ng_ran_rcu",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_needed_not_needed,
    nullptr,
    0x02,
};
const val_string pnb_ciot_values[] = {
    {0, "no additional information"},
    {1, "control plane CIot 5GS optimization"},
    {2, "user plane CIot 5GS optimization"},
    {3, "reserved"},
    {0, nullptr},
};
const field_meta mm::hf_pnb_ciot = {
    "",
    "nas_5gs.mm.pnb_ciot",
    ft::ft_uint8,
    fd::base_dec,
    pnb_ciot_values, nullptr, nullptr,0,
};

// 9.11.3.9A 5GS update type
int mm::dissect_update_type(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b3,
        &hf_pnb_ciot,
        &hf_ng_ran_rcu,
        &hf_sms_requested,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

#if 0
/* 9.11.3.37    NSSAI*/
int mm::dissect_requested_nssai(dissector d, context* ctx) {
    auto len = d.length;
    auto i = 1;
    while(d.length>0){
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "S-NSSAI %u", i);
        use_tree ut(d, subtree);

        auto length = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
        ++i;
    }
    return len;
}
#endif



int mm::dissect_reg_req_type(dissector d, context* ctx) {
    const field_meta* flags[] = {
        &hf_mm_for,
        &hf_mm_reg_type,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

/* 9.11.3.2A    5GS DRX parameters*/
int mm::dissect_requested_drx_param(dissector d, context* ctx) {
    return dissect_drx_param(d, ctx);
    // d.add_item(1, &hf_drx_param, enc::be);
}
