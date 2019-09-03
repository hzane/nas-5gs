#include "dissect_mm_msg.hh"
#include <cassert>
#include "gsm.hh"
#include "ts24007.hh"

using namespace nas;
using namespace mm;

/*
 * 8.2.13 De-registration accept (UE originating de-registration)
 */
/* No data */

/*
 * 8.2.15 De-registration accept (UE terminated de-registration)
 */
/* No data */

/*
 * 9.11.3.10    ABBA
 */
int dissect_abba(dissector d, context* ctx) {
    d.add_item(d.length, &hf_abba, enc::be);
    return d.length;
}

/* 9.11.2.8    S-NSSAI */
//  a type 4 information element
int mm::dissect_s_nssai(dissector d, context* ctx) {
    auto len = d.length;
    /* SST    octet 3
     * This field contains the 8 bit SST value. The coding of the SST value part is
     * defined in 3GPP TS 23.003
     */
    d.add_item(1, &hf_sst, enc::be);
    d.step(1);
    if (len == 1) return len;

    /* SD    octet 4 - octet 6* */
    d.add_item(3, &hf_sd, enc::be);
    d.step(3);

    if (len == 4) return len;

    /* Mapped configured SST    octet 7* */
    d.add_item(1, &hf_mapped_conf_sst, enc::be);
    d.step(1);
    if (len == 5) return len;

    /* Mapped configured SD    octet 8 - octet 10* */
    d.add_item(3, &hf_mapped_conf_ssd, enc::be);
    d.step(3);

    d.extraneous_data_check(0);
    return len;
}

/*
 * 9.11.3.37    NSSAI
 * S-NSSAI value is coded as the length and value part of S-NSSAI information element
as specified in subclause 9.11.2.8 starting with the second octet.
 */
int mm::dissect_allowed_nssai(dissector d, context* ctx) {

    auto len = d.length;
    auto i   = 1;
    while (d.length > 0) {
        auto     subtree = d.add_item(-1, "S-NSSAI %u", i);
        use_tree ut(d, subtree);

        auto l       = d.uint8();
        auto item    = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_s_nssai(d.slice(l), ctx);
        d.step(consumed);
        d.tree->set_length(consumed + 1);

        ++i;
    }
    return len;
}

/* 9.11.3.37    NSSAI*/
int mm::dissect_requested_nssai(dissector d, context* ctx) {
    const auto len = d.length;
    auto i = 1;
    while(d.length>0){
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "S-NSSAI %u", i);
        use_tree ut(d, subtree);

        auto length = static_cast< int >(d.tvb->uint8(d.offset));
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);
        // 9.11.2.8
        auto consumed = dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
        ++i;
    }
    return len;
}

const true_false_string eps_emm_ebi_vals = {
    "BEARER CONTEXT-ACTIVE",
    "BEARER CONTEXT-INACTIVE",
};

const field_meta hf_eps_emm_ebi7 = {
    "EBI(7)",
    "nas_eps.emm.ebi7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x80,
};
const field_meta hf_eps_emm_ebi6 = {
    "EBI(6)",
    "nas_eps.emm.ebi6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x40,
};
const field_meta hf_eps_emm_ebi5 = {
    "EBI(5)",
    "nas_eps.emm.ebi5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x20,
};
const field_meta hf_eps_emm_ebi4 = {
    "EBI(4)",
    "nas_eps.emm.ebi4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x10,
};
const field_meta hf_eps_emm_ebi3 = {
    "EBI(3)",
    "nas_eps.emm.ebi3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x08,
};
const field_meta hf_eps_emm_ebi2 = {
    "EBI(2)",
    "nas_eps.emm.ebi2",
    ft::ft_boolean,
    8,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x04,
};
const field_meta hf_eps_emm_ebi1 = {
    "EBI(1)",
    "nas_eps.emm.ebi1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x02,
};
const field_meta hf_eps_emm_ebi0 = {
    "EBI(0) spare",
    "nas_eps.emm.ebi0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
};

const field_meta hf_eps_emm_ebi15 = {
    "EBI(15)",
    "nas_eps.emm.ebi15",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x80,
};
const field_meta hf_eps_emm_ebi14 = {
    "EBI(14)",
    "nas_eps.emm.ebi14",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x40,
};
const field_meta hf_eps_emm_ebi13 = {
    "EBI(13)",
    "nas_eps.emm.ebi13",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x20,
};
const field_meta hf_eps_emm_ebi12 = {
    "EBI(12)",
    "nas_eps.emm.ebi12",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x10,
};
const field_meta hf_eps_emm_ebi11 = {
    "EBI(11)",
    "nas_eps.emm.ebi11",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x08,
};
const field_meta hf_eps_emm_ebi10 = {
    "EBI(10)",
    "nas_eps.emm.ebi10",
    ft::ft_boolean,
    8,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x04,
};
const field_meta hf_eps_emm_ebi9  = {
    "EBI(9)",
    "nas_eps.emm.ebi9",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x02,
};
const field_meta hf_eps_emm_ebi8  = {
    "EBI(8)",
    "nas_eps.emm.ebi8",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,&eps_emm_ebi_vals,nullptr,
    0x01,
};

/*  9.11.3.59  EPS bearer context status
 * See subclause 9.9.2.1 in 3GPP TS 24.301 [15]. */
int mm::dissect_eps_bearer_context_status(dissector d, context* ctx) {
    const field_meta* flags[] = {
        &hf_eps_emm_ebi7,
        &hf_eps_emm_ebi6,
        &hf_eps_emm_ebi5,
        &hf_eps_emm_ebi4,
        &hf_eps_emm_ebi3,
        &hf_eps_emm_ebi2,
        &hf_eps_emm_ebi1,
        &hf_eps_emm_ebi0,
        nullptr,
    };
    const field_meta* flags2[] = {
        &hf_eps_emm_ebi15,
        &hf_eps_emm_ebi14,
        &hf_eps_emm_ebi13,
        &hf_eps_emm_ebi12,
        &hf_eps_emm_ebi11,
        &hf_eps_emm_ebi10,
        &hf_eps_emm_ebi9,
        &hf_eps_emm_ebi8,
        nullptr,
    };
    /* EBI(7)  EBI(6)  EBI(5)  EBI(4)  EBI(3)  EBI(2)  EBI(1) EBI(0) octet 3 */
    /* EBI(0): Bit 1 of octet 3 is spare and shall be coded as zero. */
    d.add_bits(flags);
    d.step(1);
    /* EBI(15) EBI(14) EBI(13) EBI(12) EBI(11) EBI(10) EBI(9) EBI(8) octet 4 */
    d.add_bits(flags2);
    d.step(1);
    return 2;
}

/*
 * 9.11.3.9     5GS tracking area identity list
 */
extern const value_string nas_5gs_mm_tal_t_li_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0, nullptr},
};

extern const value_string nas_5gs_mm_tal_num_e[] = {
    {0x00, "1 element"},
    {0x01, "2 elements"},
    {0x02, "3 elements"},
    {0x03, "4 elements"},
    {0x04, "5 elements"},
    {0x05, "6 elements"},
    {0x06, "7 elements"},
    {0x07, "8 elements"},
    {0x08, "9 elements"},
    {0x09, "10 elements"},
    {0x0a, "11 elements"},
    {0x0b, "12 elements"},
    {0x0c, "13 elements"},
    {0x0d, "14 elements"},
    {0x0e, "15 elements"},
    {0x0f, "16 elements"},
    {0, nullptr},
};
const field_meta mm::hf_tal_t_li = {
    "Type of list",
    "nas_5gs.mm.tal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_tal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
const field_meta mm::hf_tal_num_e = {
    "Number of elements",
    "nas_5gs.mm.tal_num_e",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_mm_tal_num_e),
    nullptr,
    nullptr,
    0x1f,
};
const field_meta mm::hf_tac = {
    "TAC",
    "nas_5gs.tac",
    ft::ft_uint24,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

// 9.11.3.9	5GS tracking area identity list
int mm::dissect_ta_id_list(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_tal_t_li,
        &hf_tal_num_e,
        nullptr,
    };
    auto len         = d.length;
    auto num_par_tal = 1;
    /*Partial tracking area list*/
    while (d.length > 0) {
        auto orig_offset = d.offset;
        auto subtree     = d.add_item(-1, "Partial tracking area list  %u", num_par_tal);
        use_tree ut(d, subtree);
        /*Head of Partial tracking area list*/
        /* Type of list    Number of elements    octet 1 */
        auto head  = d.tvb->uint8(d.offset);
        auto li    = (head & 0x60u) >> 5u;
        auto num_e = (head & 0x1fu) + 1;
        d.add_bits(flags);
        d.step(1);

        switch (li) {
        case 0: { // 00
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            while (num_e > 0) {
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);

                --num_e;
            }

        } break;
        case 1: { // 01
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            /*octet 5  TAC 1*/
            d.add_item(3, &hf_tac, enc::be);
            d.step(3);
        } break;
        case 2: { // 10
            while (num_e > 0) {
                /*octet 2  MCC digit2  MCC digit1*/
                /*octet 3  MNC digit3  MCC digit3*/
                /*octet 4  MNC digit2  MNC digit1*/
                auto consumed = dissect_e212_mcc_mnc(d, ctx);
                d.step(consumed);

                /*octet 5  TAC 1*/
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);

                --num_e;
            }
        } break;
        case 3: { // All other values are reserved.
        // not defined in 24.501 16.1.0
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);
        } break;
        default:
            diag("reserved type of list %d\n", li);
            d.step(d.length); // consumed all left bytes
            break;
        }

        subtree->set_length(d.offset - orig_offset);
        /*calculate the number of Partial tracking area list*/
        num_par_tal++;
    }
    return len;
}
const val_string ref_nssai_cause_values[] = {
    {0, "S-NSSAI not available in the current PLMN"},
    {
        1,
        "S-NSSAI not available in the current registration area All other values are "
        "reserved.",
    },
    {0, nullptr},
};
const field_meta hf_rej_nssai_cause = {
    "Cause",
    "nas_5gs.mm.cause",
    ft::ft_uint8,
    fd::base_dec,
    ref_nssai_cause_values,
    nullptr,
    nullptr,
    0x0f,
};

/* *   9.11.3.46    Rejected NSSAI page.389 */
int mm::dissect_rejected_nssai(dissector d, context* ctx) {
    auto len = d.length;
    auto i = 1;
    while(d.length>0){
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "Rejected S-NSSAI %u", i);
        use_tree ut(d, subtree);

        auto len = int(d.uint8()>>4u);
        d.add_item(1, &hf_rej_nssai_cause, enc::be);
        d.step(1);

        d.add_item(1, &hf_sst, enc::be);
        d.step(1);
        if (len==1) continue; // len == 1 || len == 4

        d.add_item(3, &hf_sd, enc::be);
        d.step(3);
        ++i;
    }
    return len;
}

/* 9.11.3.37    NSSAI */
int mm::dissect_configured_nssai(dissector d, context* ctx) {
    /*S-NSSAI value is coded as the length and value part of S-NSSAI information element
     * as specified in subclause 9.11.2.8 starting with the second octet.*/
    auto len = d.length;
    auto i   = 1;
    while (d.length > 0) {
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "S-NSSAI %u", i);
        use_tree ut(d, subtree);

        int length = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_s_nssai(d.slice(length), ctx);
        d.step(consumed);

        ++i;
    }
    return len;
}


/*
 *   9.11.3.44    PDU session status
 */
namespace mm {
static true_false_string tfs_nas_5gs_pdu_ses_sts_psi = {
    "Not PDU SESSION INACTIVE",
    "PDU SESSION INACTIVE",
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_7_b7 = {
    "PSI(7)",
    "nas_5gs.pdu_ses_sts_psi_7_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_6_b6 = {
    "PSI(6)",
    "nas_5gs.pdu_ses_sts_psi_6_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_5_b5 = {
    "PSI(5)",
    "nas_5gs.pdu_ses_sts_psi_5_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_4_b4 = {
    "PSI(4)",
    "nas_5gs.pdu_ses_sts_psi_4_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_3_b3 = {
    "PSI(3)",
    "nas_5gs.pdu_ses_sts_psi_3_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_2_b2 = {
    "PSI(2)",
    "nas_5gs.pdu_ses_sts_psi_2_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_1_b1 = {
    "PSI(1)",
    "nas_5gs.pdu_ses_sts_psi_1_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_0_b0 = {
    "Spare",
    "nas_5gs.pdu_ses_sts_psi_0_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_pdu_ses_sts_psi_15_b7 = {
    "PSI(15)",
    "nas_5gs.pdu_ses_sts_psi_15_b7",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_14_b6 = {
    "PSI(14)",
    "nas_5gs.pdu_ses_sts_psi_14_b6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_13_b5 = {
    "PSI(13)",
    "nas_5gs.pdu_ses_sts_psi_13_b5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_12_b4 = {
    "PSI(12)",
    "nas_5gs.pdu_ses_sts_psi_12_b4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_11_b3 = {
    "PSI(11)",
    "nas_5gs.pdu_ses_sts_psi_11_b3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_10_b2 = {
    "PSI(10)",
    "nas_5gs.pdu_ses_sts_psi_10_b2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_9_b1 = {
    "PSI(9)",
    "nas_5gs.pdu_ses_sts_psi_9_b1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_sts_psi_8_b0 = {
    "PSI(8)",
    "nas_5gs.pdu_ses_sts_psi_8_b0",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_pdu_ses_sts_psi,
    nullptr,
    0x01,
};
} // namespace mm

// PDU session status   9.11.3.44
int mm::dissect_pdu_ses_status(dissector d, context* ctx) {
    static const field_meta* psi_0_7_flags[] = {
        &hf_nas_5gs_pdu_ses_sts_psi_7_b7,
        &hf_nas_5gs_pdu_ses_sts_psi_6_b6,
        &hf_nas_5gs_pdu_ses_sts_psi_5_b5,
        &hf_nas_5gs_pdu_ses_sts_psi_4_b4,
        &hf_nas_5gs_pdu_ses_sts_psi_3_b3,
        &hf_nas_5gs_pdu_ses_sts_psi_2_b2,
        &hf_nas_5gs_pdu_ses_sts_psi_1_b1,
        &hf_nas_5gs_pdu_ses_sts_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_nas_5gs_pdu_ses_sts_psi_15_b7,
        &hf_nas_5gs_pdu_ses_sts_psi_14_b6,
        &hf_nas_5gs_pdu_ses_sts_psi_13_b5,
        &hf_nas_5gs_pdu_ses_sts_psi_12_b4,
        &hf_nas_5gs_pdu_ses_sts_psi_11_b3,
        &hf_nas_5gs_pdu_ses_sts_psi_10_b2,
        &hf_nas_5gs_pdu_ses_sts_psi_9_b1,
        &hf_nas_5gs_pdu_ses_sts_psi_8_b0,
        nullptr,
    };

    const auto len = d.length;

    d.add_bits(psi_0_7_flags);
    d.step(1);

    d.add_bits(psi_8_15_flags);
    d.step(1);

    // All bits in octet 5 to 34 are spare and shall be coded as zero, if the respective octet is included in the information element
    // d.extraneous_data_check(0);
    return len;
}

//  *   9.11.3.42    PDU session reactivation result
const true_false_string tfs_nas_5gs_pdu_ses_rect_res_psi     = {"1", "0"};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_7_b7 = {
    "PSI(7)",
    "nas_5gs.pdu_ses_rect_res_psi_3_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_6_b6 = {
    "PSI(6)",
    "nas_5gs.pdu_ses_rect_res_psi_3_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_5_b5 = {
    "PSI(5)",
    "nas_5gs.pdu_ses_rect_res_psi_3_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_4_b4 = {
    "PSI(4)",
    "nas_5gs.pdu_ses_rect_res_psi_3_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_3_b3 = {
    "PSI(3)",
    "nas_5gs.pdu_ses_rect_res_psi_3_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_2_b2 = {
    "PSI(2)",
    "nas_5gs.pdu_ses_rect_res_psi_2_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_1_b1 = {
    "PSI(1)",
    "nas_5gs.pdu_ses_rect_res_psi_1_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_0_b0 = {
    "PSI(0) Spare",
    "nas_5gs.pdu_ses_rect_res_psi_0_b0",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x01,
};

const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_15_b7 = {
    "PSI(15)",
    "nas_5gs.pdu_ses_sts_psi_15_b7",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x80,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_14_b6 = {
    "PSI(14)",
    "nas_5gs.pdu_ses_sts_psi_14_b6",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x40,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_13_b5 = {
    "PSI(13)",
    "nas_5gs.pdu_ses_sts_psi_13_b5",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x20,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_12_b4 = {
    "PSI(12)",
    "nas_5gs.pdu_ses_rect_res_psi_12_b4",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x10,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_11_b3 = {
    "PSI(11)",
    "nas_5gs.pdu_ses_rect_res_psi_11_b3",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x08,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_10_b2 = {
    "PSI(10)",
    "nas_5gs.pdu_ses_rect_res_psi_10_b2",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x04,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_9_b1  = {
    "PSI(9)",
    "nas_5gs.pdu_ses_rect_res_psi_9_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_8_b0  = {
    "PSI(8)",
    "nas_5gs.pdu_ses_rect_res_psi_8_b0",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x01,
};

// PDU session reactivation result   9.11.3.42
int mm::dissect_pdu_ses_react_res(dissector d, context* ctx) {
    auto len = d.length;
    static const field_meta* psi_0_7_flags[] = {
        &hf_nas_5gs_pdu_ses_rect_res_psi_7_b7,
        &hf_nas_5gs_pdu_ses_rect_res_psi_6_b6,
        &hf_nas_5gs_pdu_ses_rect_res_psi_5_b5,
        &hf_nas_5gs_pdu_ses_rect_res_psi_4_b4,
        &hf_nas_5gs_pdu_ses_rect_res_psi_3_b3,
        &hf_nas_5gs_pdu_ses_rect_res_psi_2_b2,
        &hf_nas_5gs_pdu_ses_rect_res_psi_1_b1,
        &hf_nas_5gs_pdu_ses_rect_res_psi_0_b0,
        nullptr,
    };

    static const field_meta* psi_8_15_flags[] = {
        &hf_nas_5gs_pdu_ses_rect_res_psi_15_b7,
        &hf_nas_5gs_pdu_ses_rect_res_psi_14_b6,
        &hf_nas_5gs_pdu_ses_rect_res_psi_13_b5,
        &hf_nas_5gs_pdu_ses_rect_res_psi_12_b4,
        &hf_nas_5gs_pdu_ses_rect_res_psi_11_b3,
        &hf_nas_5gs_pdu_ses_rect_res_psi_10_b2,
        &hf_nas_5gs_pdu_ses_rect_res_psi_9_b1,
        &hf_nas_5gs_pdu_ses_rect_res_psi_8_b0,
        nullptr,
    };
    d.add_bits(psi_0_7_flags);
    d.step(1);
    d.add_bits(psi_8_15_flags);
    d.step(1);

    // 5-34 is optional

    return len;
}

// 9.11.3.2	5GMM cause
int mm::dissect_mm_cause(dissector d, context* ctx) {
    auto cause = d.tvb->uint8(d.offset);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, &hf_mm_cause, enc::be);
    return 1;
}
/*  9.11.3.29    LADN indication  */
int mm::dissect_ladn_ind(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 1;
    while(d.length>0){
        auto subtree = d.add_item(2, "LADN DNN value %u", i);
        use_tree ut(d, subtree);
        /*LADN DNN value is coded as the length and value part of DNN information element
         * as specified in subclause 9.11.2.1A starting with the second octet*/
        int length = (int)d.uint8();
        d.step(1);

        auto consumed = dissect_dnn(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
        ++i;
    }
    return len;
}
/*  9.11.3.30    LADN information  */
int mm::dissect_ladn_inf(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 1;
    while (d.length > 0) {
        auto     start   = d.offset;
        auto     subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "LADN %u", i);
        use_tree ut(d, subtree);

        /* DNN value (octet 5 to octet m):
         * LADN DNN value is coded as the length and value part of DNN information
         * element as specified in subclause 9.11.2.1A starting with the second octet
         */
        auto length = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_dnn(d.slice(length), ctx);
        d.step(consumed);

        /* 5GS tracking area identity list (octet m+1 to octet a):
         * 5GS tracking area identity list field is coded as the length and the value
         * part of the 5GS Tracking area identity list information element as
         * specified in subclause 9.11.3.9 starting with the second octet
         */
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        length   = d.tvb->uint8(d.offset);
        consumed = dissect_ta_id_list(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(d.offset - start);

        ++i;
    }
    return len;
}

/*  9.11.3.31    MICO indication */
static const true_false_string tfs_raai = {
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};

/*  9.11.3.31    MICO indication */
int mm::dissect_mico_ind(dissector d, context* ctx) {
    auto len = d.length;

    d.add_item(1, hf_mm_raai_b0, enc::be);

    // In the UE to network direction bit 1 is spare. The UE shall set this bit to
    // zero. In the network to UE and the UE to network direction:
    d.add_item(1, &hf_mm_sprti, enc::be);
    return 1;
}

namespace mm {
const field_meta hf_sal_al_t = {
    "Allowed type",
    "nas_5gs.mm.sal_al_t",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_sal_al_t,
    nullptr,
    0x80,
};
const field_meta hf_sal_t_li = {
    "Type of list",
    "nas_5gs.mm.sal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    mm_sal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
} // namespace mm

// 9.11.3.49    Service area list page.391
int mm::dissect_sal(dissector d, context* ctx) {
    auto                     len     = d.length;
    static const field_meta* flags[] = {
        &hf_sal_al_t,
        &hf_sal_t_li,
        &hf_sal_num_e,
        nullptr,
    };
    auto num_par_sal = 1;
    /*Partial service area list*/
    while (d.length > 0) {
        auto     start   = d.offset;
        auto     subtree = d.add_item(-1, "Partial service area list  %u", num_par_sal);
        use_tree ut(d, subtree);

        /*Head of Partial service area list*/
        /* Allowed type    Type of list    Number of elements    octet 1 */
        auto sal_head  = d.tvb->uint8(d.offset);
        auto sal_t_li  = (sal_head & 0x60) >> 5;
        auto sal_num_e = (sal_head & 0x1f) + 1;
        d.add_bits(flags);
        d.step(1);
        switch (sal_t_li) {
        case 0: { // type of list = "00"
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
            while (sal_num_e > 0) {
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);
                --sal_num_e;
            }
        } break;
        case 1: { // type of list = "01"
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);

            /*octet 5  TAC 1*/
            d.add_item(3, &hf_tac, enc::be);
            d.step(3);
        } break;
        case 2: { // type of list = "10"
            while (sal_num_e > 0) {
                /*octet 2  MCC digit2  MCC digit1*/
                /*octet 3  MNC digit3  MCC digit3*/
                /*octet 4  MNC digit2  MNC digit1*/
                dissect_e212_mcc_mnc(d, ctx);
                d.step(3);

                /*octet 5  TAC 1*/
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);
                --sal_num_e;
            }
        } break;
        case 3: { // type of list = "11"
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
        } break;
        default: // never goes here
            break;
        }

        /*calculate the length of IE */
        d.tree->set_length(d.offset - start);
        /*calculate the number of Partial service area list*/
        num_par_sal++;
    }
    return len;
    }

    namespace mm {
        const val_string nas_5gs_mm_supi_fmt_vals[] = {
            {0x0, "IMSI"},
            {0x1, "Network Specific Identifier"},
            {0, nullptr},
        };
        const field_meta hf_nas_5gs_mm_supi_fmt = {
            "SUPI format",
            "nas_5gs.mm.suci.supi_fmt",
            ft::ft_uint8,
            fd::base_dec,
            (nas_5gs_mm_supi_fmt_vals),
            nullptr,
            nullptr,
            0x70,
        };

        const field_meta hf_nas_5gs_mm_suci_nai = {
            "NAI",
            "nas_5gs.mm.suci.nai",
            ft::ft_bytes,
            fd::base_string,
            nullptr,
            nullptr,
            nullptr,
            0,
        };
        const field_meta hf_nas_5gs_mm_imei = {
            "IMEI",
            "nas_5gs.mm.imei",
            ft::ft_bytes,
            fd::base_hex,
            nullptr,
            nullptr,
            nullptr,
            0,
        };
        const field_meta hf_nas_5gs_mm_imeisv = {
            "IMEISV",
            "nas_5gs.mm.imeisv",
            ft::ft_bytes,
            fd::base_hex,
            nullptr,
            nullptr,
            nullptr,
            0,
        };
        const field_meta hf_nas_5gs_amf_set_id = {
            "AMF Set ID",
            "nas_5gs.amf_set_id",
            ft::ft_uint16,
            fd::base_dec,
            nullptr,
            nullptr,
            nullptr,
            0xffc0,
        };
        const field_meta hf_nas_5gs_amf_pointer = {
            "AMF Pointer",
            "nas_5gs.amf_pointer",
            ft::ft_uint8,
            fd::base_dec,
            nullptr,
            nullptr,
            nullptr,
            0x3f,
        };
        const field_meta hf_nas_5gs_tmsi = {
            "5G-TMSI",
            "nas_5gs.5g_tmsi",
            ft::ft_uint32,
            fd::base_hex,
            nullptr,
            nullptr,
            nullptr,
            0x0,
        };
    } // namespace mm

    const field_meta hf_mm_routing_ind = {
        "Routing indicator",
        "nas_5gs.mm.suci.routing_indicator",
        ft::ft_bytes,
        fd::base_string,
        nullptr,
        nullptr,
        nullptr,
        0,
    };
    static const value_string nas_5gs_mm_prot_scheme_id_vals[] = {
        {0x0, "NULL scheme"},
        {0x1, "ECIES scheme profile A"},
        {0x2, "ECIES scheme profile B"},
        {0, nullptr},
    };

    const field_meta hf_mm_prot_scheme_id = {
        "Protection scheme Id",
        "nas_5gs.mm.suci.scheme_id",
        ft::ft_uint8,
        fd::base_dec,
        (nas_5gs_mm_prot_scheme_id_vals),
        nullptr,
        nullptr,
        0x0f,
    };
    const field_meta hf_mm_pki = {
        "Home network public key identifier",
        "nas_5gs.mm.suci.pki",
        ft::ft_uint8,
        fd::base_dec,
        nullptr,
        nullptr,
        nullptr,
        0x0,
    };

    const field_meta hf_mm_supi_null_scheme = {
        "Scheme output",
        "nas_5gs.mm.suci.supi_null_scheme",
        ft::ft_bytes,
        fd::base_string,
        nullptr,
        nullptr,
        nullptr,
        0,
    };

    const field_meta hf_mm_scheme_output = {
        "Scheme output",
        "nas_5gs.mm.suci.scheme_output",
        ft::ft_bytes,
        fd::base_none,
        nullptr,
        nullptr,
        nullptr,
        0x0,
    };

    const field_meta hf_amf_region_id = {
        "AMF Region ID",
        "nas_5gs.amf_region_id",
        ft::ft_uint8,
        fd::base_dec,
        nullptr,
        nullptr,
        nullptr,
        0x0,
    };
    const field_meta hf_amf_set_id = {
        "AMF Set ID",
        "nas_5gs.amf_set_id",
        ft::ft_uint16,
        fd::base_dec,
        nullptr,
        nullptr,
        nullptr,
        0xffc0,
    };
    const field_meta hf_amf_pointer = {
        "AMF Pointer",
        "nas_5gs.amf_pointer",
        ft::ft_uint8,
        fd::base_dec,
        nullptr,
        nullptr,
        nullptr,
        0x3f,
    };
    const field_meta hf_5g_tmsi = {
        "5G-TMSI",
        "nas_5gs.5g_tmsi",
        ft::ft_uint32,
        fd::base_hex,
        nullptr,
        nullptr,
        nullptr,
        0x0,
    };

    const field_meta hf_mac_address = {
        "MAC address",
        "nas_5gs.mac",
        ft::ft_bytes,
        fd::sep_colon,
        nullptr,
        nullptr,
        nullptr,
        0,
    };
    namespace {
        static const field_meta* flags_odd_even_tid[] = {
            &hf_mm_odd_even,
            &hf_mm_type_id,
            nullptr,
        };

        static const field_meta* flags_supi_fmt_tid[] = {
            &hf_spare_b7,
            &hf_nas_5gs_mm_supi_fmt,
            &hf_spare_b3,
            &hf_mm_type_id,
            nullptr,
        };
    }
    // type_id = 6, MAC address
    int mm::dissect_mobile_id_mac(dissector d, context * ctx) {
        d.add_bits(flags_odd_even_tid);
        d.step(1);

        d.add_item(6, &hf_mac_address, enc::be);
        d.step(6);

        d.extraneous_data_check(0);
        return 7;
    }
    // type_id = 0, no identity
    int mm::dissect_mobile_id_noid(dissector d, context * ctx) {
        d.add_bits(flags_odd_even_tid);
        d.step(1);

        d.extraneous_data_check(0);
        return 1;
    }

    // type_id = 4, 5G-S-TMSI
    int mm::dissect_mobile_id_5gstmsi(dissector d, context * ctx) {
        d.add_bits(flags_odd_even_tid);
        d.step(1);

        /* AMF Set ID */
        auto item = d.add_item(2, &hf_nas_5gs_amf_set_id, enc::be);

        d.step(1);
        /* AMF Pointer AMF Set ID (continued) */
        d.add_item(1, &hf_nas_5gs_amf_pointer, enc::be);
        d.step(1);

        d.add_item(4, &hf_nas_5gs_tmsi, enc::be);
        d.step(4);

        d.extraneous_data_check(0);
        return 7;
    }

    // type_id = 1, SUCI
    int mm::dissect_mobile_id_suci(dissector d, context * ctx) {
        auto oct = d.uint8();
        d.add_bits(flags_supi_fmt_tid);
        d.step(1);

        const auto supi_fmt = oct & 0x70;
        if (supi_fmt == 0) { // IMSI
            /* MCC digit 2    MCC digit 1
             * MNC digit 3    MCC digit 3
             * MNC digit 2    MNC digit 1             */
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            /* Routing indicator octet 8-9 */
            d.add_item(2, &hf_mm_routing_ind, enc::na);
            d.step(2);

            /* Protection scheme id octet 10 */
            const auto scheme_id = d.uint8() & 0x0fu;
            d.add_item(1, &hf_mm_prot_scheme_id, enc::be);
            d.step(1);

            /* Home network public key identifier octet 11 */
            d.add_item(1, &hf_mm_pki, enc::be);
            d.step(1);

            /* Scheme output octet 12-x */
            if (scheme_id == 0) { // Null scheme
                d.add_item(d.length, &hf_mm_supi_null_scheme, enc::be);
            } else {
                d.add_item(d.length, &hf_mm_scheme_output, enc::na);
            }
            d.step(d.length);
        } else if (supi_fmt == 1) { // nai, network specific identifier
            d.add_item(d.length, &hf_nas_5gs_mm_suci_nai, enc::be);
        } else {
            diag("unknown supi format %d\n", supi_fmt);
        }
        return d.length;
    }

// type_id = 2, 5G-GUTI
int mm::dissect_mobile_id_5gguti(dissector d, context* ctx){
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    /* MCC digit 2    MCC digit 1
     * MNC digit 3    MCC digit 3
     * MNC digit 2    MNC digit 1 */
    auto consumed = dissect_e212_mcc_mnc(d, ctx);
    d.step(consumed);

    /* AMF Region ID octet 7 */
    d.add_item(1, &hf_amf_region_id, enc::be);
    d.step(1);

    /* AMF Set ID octet 8 */
    d.add_item(1, &hf_amf_set_id, enc::be);
    d.step(1);

    /* AMF AMF Pointer AMF Set ID (continued) */
    d.add_item(1, &hf_amf_pointer, enc::be);
    d.step(1);

    d.add_item(4, &hf_5g_tmsi, enc::be);
    d.step(4);
    return 11;
}

// type_id = 3, IMEI
int mm::dissect_mobile_id_imei(dissector d, context* ctx){
    auto len = d.length;
    d.add_bits(flags_odd_even_tid);
    d.step(1);

    d.add_item(d.length, &hf_nas_5gs_mm_imeisv, enc::be);
    d.step(d.length);
    return len;
}

// type_id = 5, IMEISV
int mm::dissect_mobile_id_imeisv(dissector d, context* ctx) {
    return dissect_mobile_id_imei(d, ctx);
}


// 9.11.3.4
int mm::dissect_mobile_id(dissector d, context* ctx) {
    const auto len     = d.length;
    const auto oct     = d.uint8();
    const auto type_id = oct & 0x07u;


    switch (type_id) {
    case 0: { // no identity
        d.add_bits(flags_odd_even_tid);
    } break;
    case 1: { // SUCI
        auto consumed = dissect_mobile_id_suci(d, ctx);
        d.step(consumed);
    } break;
    case 2: { // 5G-GUTI
        auto consumed = dissect_mobile_id_5gguti(d, ctx);
        d.step(consumed);
    } break;
    case 3: { // IMEI
        dissect_mobile_id_imei(d, ctx);
        d.step(d.length);
    } break;
    case 4: { // 5G-S-TMSI
        auto consumed = dissect_mobile_id_5gstmsi(d, ctx);
        d.step(consumed);
    } break;
    case 5: { // IMEISV
        dissect_mobile_id_imeisv(d, ctx);
        d.step(d.length);
    } break;
    case 6: { // MAC address
        dissect_mobile_id_mac(d, ctx);
        d.step(7);
    } break;
    default: {
        auto item = d.add_item(1, &hf_mm_type_id, enc::be);
        diag("unknown mobile type id %d\n", type_id);
    } break;
    }

    return len;
}

/*  9.11.3.39    Payload container */
int mm::dissect_pld_cont(dissector d, context* ctx) {
    auto len = d.length;

    auto typi = d.get_private("payload-content-type", 0);
    switch (typi) {
    case 1: { /* N1 SM information */
        dissect_nas5g_plain(d, ctx);
    } break;
    case 2: { // SMS
        d.add_item(d.length, &hf_pld_cont, enc::na);
    } break;
    case 3: { // LPP
        d.add_item(d.length, &hf_pld_cont, enc::na);
    } break;
    case 5: { /* UE policy container */
        dissect_updp(d, ctx);
    } break;
    default:
        d.add_item(d.length, &hf_pld_cont, enc::na);
    }

    return len;
}
int mm::dissect_pld_cont_type(dissector d, context* ctx) {
    auto oct = d.tvb->uint8(d.offset);
    d.set_private("payload-content-type", oct);

    d.add_item(1, &hf_pld_cont_type, enc::be);
    return 1;
}
/* 9-  Network slicing indication  Network slicing indication 9.11.3.36  O  TV 1 */
static const true_false_string nas_5gs_mm_dcni_tfs = {
    "Requested NSSAI created from default configured NSSAI",
    "Requested NSSAI not created from default configured NSSAI",
};
const field_meta hf_dcni = {
    "Default configured NSSAI indication (DCNI)",
    "nas_5gs.mm.dcni",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_mm_dcni_tfs,
    nullptr,
    0x02,
};
const true_false_string tfs_changed_not_changed = {"Changed", "Not Changed"};
const field_meta        hf_nssci                = {
    "Network slicing subscription change indication (NSSCI)",
    "nas_5gs.mm.nssci",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_changed_not_changed,
    nullptr,
    0x01,
};

//  9.11.3.36    Network slicing indication
int mm::dissect_nw_slicing_ind(dissector d, context* ctx) {
    static const field_meta* flags[] = {
        &hf_spare_b3,
        &hf_spare_b2,
        &hf_dcni,
        &hf_nssci,
        nullptr,
    };
    d.add_bits(flags);
    return 1;
}

// 9.11.3.32	NAS key set identifier
int mm::dissect_nas_ksi(dissector d, context*ctx) {
    use_context uc(ctx, "NAS key set identifier");

    static const field_meta* flags[] = {
        &hf_tsc,
        hf_nas_eps_nas_ksi, //& hf_nas_key_set_id,
        nullptr,
    };

    /* NAS key set identifier IEI   TSC     NAS key set identifier */
    d.add_bits(flags);

    return 1;
}

// nas key set id nas-key-set-id
int dissect_nas_ksi_obs(dissector d, context* ctx) {
    auto v = d.tvb->uint8(d.offset);

    /* Type of security context flag (TSC) (octet 1)    V   1/2   */
    auto tsc  = (v & 0x10) >> 4;
    auto item = d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_nas_eps_tsc, enc::none);
    item->set_uint(tsc, enc::be, nullptr);

    auto nas_ksi = (v & 0xe0) >> 5;
    item         = d.add_item(1, hf_nas_eps_nas_ksi, enc::none);
    item->set_uint(nas_ksi, enc::be, nullptr);

    return 1;
}

/*
 * 9.4.14a  Mobile Station Classmark 2
 * With the exception of the IEI, the contents are specified in subclause 10.5.1.6 in 3GPP
 * TS 24.008 [8]. (packet-gsm_a_common.c)
 */
/*
 * 9.4.15   NAS message container
 * Octets 3 to 253 contain the SMS message (i.e. CP DATA, CP ACK or CP ERROR)
 * as defined in subclause 7.2 of 3GPP TS 24.011 [10]
 */
int mm::dissect_nas_msg_cont(dissector d, context* ctx) {
    /* Octets 3 to 253 contain the SMS message (i.e. CP DATA, CP ACK or CP ERROR)
     * as defined in subclause 7.2 of 3GPP TS 24.011 [10]
     */
    dissect_nas5g(d, ctx);
    return d.length;
}

/* 9.11.3.10    ABBA */
int mm::dissect_abba(dissector d, context* ctx) {
    // indicate set of security features defined for 5GS as described in 3GPP TS 33.501 [24].
    d.add_item(d.length, &hf_abba, enc::be);
    return d.length;
}

/* UPDP */
/* D.6.1 UE policy delivery service message type */
int mm::dissect_updp(dissector d, context* ctx) {
    auto len = d.length;

    /* 9.6  Procedure transaction identity
     * Bits 1 to 8 of the third octet of every 5GSM message contain the procedure
     * transaction identity. The procedure transaction identity and its use are defined in
     * 3GPP TS 24.007
     * XXX Only 5GSM ?
     */
    d.add_item(1, hf_proc_trans_id, enc::be);
    d.step(1);

    /* Message type IE*/
    // TODO: implement
    auto oct = d.tvb->uint8(d.offset);
    d.add_item(d.length, &hf_element, enc::be);
    return len;
}
