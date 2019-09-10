#include "../dissect_mm_msg.hh"

using namespace nas;


// 9.11.3.48 S1 UE network capability page.391
// See subclause 9.9.3.34 in 3GPP TS 24.301 [15].
int mm::dissect_s1_ue_net_capability(dissector d, context* ctx) {
    const use_context        uc(ctx, "s1-ue-network-capablility", d, 0);

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
    /* EPS encryption algorithms supported (octet 3) */
    /* EEA0    128-EEA1    128-EEA2    128-EEA3    EEA4    EEA5    EEA6    EEA7 */
    d.add_bits(oct3_flags);
    d.step(1);

    /* EPS integrity algorithms supported (octet 4) */
    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 */
    d.add_bits(oct4_flags);
    d.step(1);

    /* Following octets are optional */
    if (d.length <= 0) return 2;

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

    if (d.length <= 0) return uc.length;

    /* Octet 8
     * ePCO    HC-CP CIoT    ERw/oPDN    S1-U data    UP CIoT    CP CIoT    Prose-relay
     * ProSe-dc
     */
    d.add_bits(oct8_flags);
    d.step(1);

    if (d.length <= 0) return uc.length;

    /* Octet 9
     * 0 Spare    SGC    N1mode    DCNR    CP backoff    RestrictEC    V2X PC5 multipleDRB
     */
    // hf_nas_eps_spare_bits
    d.add_bits(oct9_flags);
    d.step(1);

    while (d.length > 0) {
        (void) d.add_item(1, &hf_nas_eps_spare_bits, enc::be);
        d.step(1);
    }

    return uc.length;
}
// 9.11.3.48A S1 UE security capability page.391
// See subclause 9.9.3.36 in 3GPP TS 24.301 [15].
int mm::dissect_reported_s1_ue_sec_cap(dissector d, context* ctx) {
    auto len = d.length;

    static const field_meta* oct3_flags[] = {
        &hf_emm_eea0,
        &hf_emm_128eea1,
        &hf_emm_128eea2,
        &hf_emm_eea3,
        &hf_emm_eea4,
        &hf_emm_eea5,
        &hf_emm_eea6,
        &hf_emm_eea7,
        nullptr,
    };

    static const field_meta* oct4_flags[] = {
        &hf_emm_eia0,
        &hf_emm_128eia1,
        &hf_emm_128eia2,
        &hf_emm_eia3,
        &hf_emm_eia4,
        &hf_emm_eia5,
        &hf_emm_eia6,
        &hf_emm_eia7,
        nullptr,
    };

    static const field_meta* oct5_flags[] = {
        &hf_emm_uea0,
        &hf_emm_uea1,
        &hf_emm_uea2,
        &hf_emm_uea3,
        &hf_emm_uea4,
        &hf_emm_uea5,
        &hf_emm_uea6,
        &hf_emm_uea7,
        nullptr,
    };

    static const field_meta* oct6_flags[] = {
//        &hf_spare_b7,
        &hf_emm_uia1,
        &hf_emm_uia2,
        &hf_emm_uia3,
        &hf_emm_uia4,
        &hf_emm_uia5,
        &hf_emm_uia6,
        &hf_emm_uia7,
        nullptr,
    };

    static const field_meta* oct7_flags[] = {
//        &hf_spare_b7,
        &hf_emm_gea1,
        &hf_emm_gea2,
        &hf_emm_gea3,
        &hf_emm_gea4,
        &hf_emm_gea5,
        &hf_emm_gea6,
        &hf_emm_gea7,
        nullptr,
    };

    /* EPS encryption algorithms supported (octet 3) */
    d.add_bits(oct3_flags);
    d.step(1);

    /* EPS integrity algorithms supported (octet 4) */
    /* EIA0    128-EIA1    128-EIA2    128-EIA3    EIA4    EIA5    EIA6    EIA7 */
    d.add_bits(oct4_flags);
    d.step(1);

    /* Octets 5, 6, and 7 are optional. If octet 5 is included,
     * then also octet 6 shall be included and octet 7 may be included.
     */
    if (len == 2) return (len);

    /* UMTS encryption algorithms supported (octet 5)
     * UEA0    UEA1    UEA2    UEA3    UEA4    UEA5    UEA6    UEA7
     */
    d.add_bits(oct5_flags);
    d.step(1);

    /* UMTS integrity algorithms supported (octet 6) */
    /* Spare    UIA1    UIA2    UIA3    UIA4    UIA5    UIA6    UIA7 */
    d.add_bits(oct6_flags);
    d.step(1);

    if (len == 4) return (len);

    /* GPRS encryption algorithms supported (octet 7) */
    /* 0 spare    GEA1    GEA2    GEA3    GEA4    GEA5    GEA6    GEA7*/
    d.add_bits(oct7_flags);
    d.step(1);

    return (len);
}
