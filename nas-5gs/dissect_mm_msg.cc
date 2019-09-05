#include "dissect_mm_msg.hh"
#include <cassert>
#include "gsm.hh"
#include "ts24007.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

namespace {
const true_false_string tfs_sal_allowed_or_not = {
    "TAIs in the list are in the non-allowed area",
    "TAIs in the list are in the allowed area",
};
const val_string mm_sal_t_li_values[] = {
    {0x00, "list of TACs belonging to one PLMN, with non-consecutive TAC values"},
    {0x01, "list of TACs belonging to one PLMN, with consecutive TAC values"},
    {0x02, "list of TAIs belonging to different PLMNs"},
    {0x03, "All TAIs belonging to the PLMN are in the allowed area"},
    {0, nullptr},
};

} // namespace

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

        auto l    = d.uint8();
        auto item = d.add_item(1, &hf_mm_length, enc::be);
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
    auto       i   = 1;
    while (d.length > 0) {
        auto subtree = d.tree->add_subtree(d.pinfo,
                                               d.tvb,
                                               d.offset,
                                               2,
                                               "S-NSSAI %u",
                                               i);
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
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x80,
};
const field_meta hf_eps_emm_ebi6 = {
    "EBI(6)",
    "nas_eps.emm.ebi6",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x40,
};
const field_meta hf_eps_emm_ebi5 = {
    "EBI(5)",
    "nas_eps.emm.ebi5",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x20,
};
const field_meta hf_eps_emm_ebi4 = {
    "EBI(4)",
    "nas_eps.emm.ebi4",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x10,
};
const field_meta hf_eps_emm_ebi3 = {
    "EBI(3)",
    "nas_eps.emm.ebi3",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x08,
};
const field_meta hf_eps_emm_ebi2 = {
    "EBI(2)",
    "nas_eps.emm.ebi2",
    ft::ft_boolean,
    8,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x04,
};
const field_meta hf_eps_emm_ebi1 = {
    "EBI(1)",
    "nas_eps.emm.ebi1",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
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
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x80,
};
const field_meta hf_eps_emm_ebi14 = {
    "EBI(14)",
    "nas_eps.emm.ebi14",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x40,
};
const field_meta hf_eps_emm_ebi13 = {
    "EBI(13)",
    "nas_eps.emm.ebi13",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x20,
};
const field_meta hf_eps_emm_ebi12 = {
    "EBI(12)",
    "nas_eps.emm.ebi12",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x10,
};
const field_meta hf_eps_emm_ebi11 = {
    "EBI(11)",
    "nas_eps.emm.ebi11",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x08,
};
const field_meta hf_eps_emm_ebi10 = {
    "EBI(10)",
    "nas_eps.emm.ebi10",
    ft::ft_boolean,
    8,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x04,
};
const field_meta hf_eps_emm_ebi9 = {
    "EBI(9)",
    "nas_eps.emm.ebi9",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
    0x02,
};
const field_meta hf_eps_emm_ebi8 = {
    "EBI(8)",
    "nas_eps.emm.ebi8",
    ft::ft_boolean,
    fd::base_dec,
    nullptr, &eps_emm_ebi_vals, nullptr,
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
        auto subtree     = d.add_item(-1,
                                          "Partial tracking area list  %u",
                                          num_par_tal);
        use_tree ut(d, subtree);
        /*Head of Partial tracking area list*/
        /* Type of list    Number of elements    octet 1 */
        auto head  = d.tvb->uint8(d.offset);
        auto li    = (head & 0x60u) >> 5u;
        auto num_e = (head & 0x1fu) + 1;
        d.add_bits(flags);
        d.step(1);

        switch (li) {
        case 0: {
            // 00
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

        }
        break;
        case 1: {
            // 01
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            /*octet 5  TAC 1*/
            d.add_item(3, &hf_tac, enc::be);
            d.step(3);
        }
        break;
        case 2: {
            // 10
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
        }
        break;
        case 3: {
            // All other values are reserved.
            // not defined in 24.501 16.1.0
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);
        }
        break;
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
    auto i   = 1;
    while (d.length > 0) {
        auto subtree = d.tree->add_subtree(d.pinfo,
                                           d.tvb,
                                           d.offset,
                                           2,
                                           "Rejected S-NSSAI %u",
                                           i);
        use_tree ut(d, subtree);

        auto len = int(d.uint8() >> 4u);
        d.add_item(1, &hf_rej_nssai_cause, enc::be);
        d.step(1);

        d.add_item(1, &hf_sst, enc::be);
        d.step(1);
        if (len == 1) continue; // len == 1 || len == 4

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
        auto subtree = d.tree->add_subtree(d.pinfo,
                                               d.tvb,
                                               d.offset,
                                               2,
                                               "S-NSSAI %u",
                                               i);
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
const field_meta        hf_nas_5gs_pdu_ses_rect_res_psi_7_b7 = {
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
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_9_b1 = {
    "PSI(9)",
    "nas_5gs.pdu_ses_rect_res_psi_9_b1",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    (&tfs_nas_5gs_pdu_ses_rect_res_psi),
    nullptr,
    0x02,
};
const field_meta hf_nas_5gs_pdu_ses_rect_res_psi_8_b0 = {
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
    auto                     len             = d.length;
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


/*  9.11.3.29    LADN indication  */
int mm::dissect_ladn_ind(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 1;
    while (d.length > 0) {
        auto     subtree = d.add_item(2, "LADN DNN value %u", i);
        use_tree ut(d, subtree);
        /*LADN DNN value is coded as the length and value part of DNN information element
         * as specified in subclause 9.11.2.1A starting with the second octet*/
        int length = (int) d.uint8();
        d.step(1);

        auto consumed = dissect_dnn(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(length + 1);
        ++i;
    }
    return len;
}


namespace mm {

} // namespace mm



namespace mm {

} // namespace mm



const field_meta hf_pld_cont_entry_nie = {
    "Number of optional IEs",
    "nas_5gs.mm.pld_cont.n_optional_ies",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0u,
};
const field_meta hf_pld_cont_entry_contents = {
    "Payload container entry contents",
    "nas_5gs.mm.pld_cont.pcec",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pld_optional_ie = {
    "Optional IE",
    "nas_5gs.mm.pld_cont.optional_ie",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const value_string pld_optional_ie_type_values[] = {
    {0x12, "PDU session ID"},         // see subclause 9.11.3.41
    {0x24, "Additional information"}, // 9.11.2.1
    {0x58, "5GMM cause"},             // 9.11.3.2
    {0x37, "Back-off timer value"},   // 9.11.2.5
    {0x59, "Old PDU session ID"},     // 9.11.3.41
    {0x80, "Request type"},           // 9.11.3.47
    {0x22, "S-NSSAI"},                // 9.11.2.8
    {0x25, "DNN"},                    // 9.11.2.1A
    {0, nullptr},
};
const field_meta hf_pld_optional_ie_type = {
    "Type of Optional IE",
    "nas_5gs.mm.pld_cont.optional_ie.type",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pld_optional_ie_length = {
    "Length of Optional IE",
    "nas_5gs.mm.pld_cont.optional_ie.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pld_optional_ie_value = {
    "Value of Optional IE",
    "nas_5gs.mm.pld_cont.optional_ie.value",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

int dissect_optional_ie(dissector d, context* ctx) {
    auto start = d.offset;

    auto     subtree = d.add_item(-1, &hf_pld_optional_ie, enc::na);
    use_tree ut(d, subtree);

    d.add_item(1, &hf_pld_optional_ie_type, enc::be);
    d.step(1);

    auto len = (int) d.uint8();
    d.add_item(1, &hf_pld_optional_ie_length, enc::be);
    d.step(1);

    d.add_item(len, &hf_pld_optional_ie_value, enc::na);
    return d.offset - start;
}

int dissect_pld_cont_entry(dissector d, context* ctx) {
    auto len = (int) d.ntohs();

    d.add_item(1, &hf_pld_cont_type, enc::be);

    auto nie = (d.uint8() & 0xf0u) >> 4;
    d.add_item(1, &hf_pld_cont_entry_nie, enc::be);
    d.step(1);

    while (nie > 0) {
        auto consumed = dissect_optional_ie(d, ctx);
        d.step(consumed);

        --nie;
    }
    d.add_item(d.length, &hf_pld_cont_entry_contents, enc::na);
    return len;
}


/*  9.11.3.39    Payload container */
int mm::dissect_pld_cont(dissector d, context* ctx) {
    auto len  = d.length;
    auto typi = retrive_payload_content_type(ctx) & 0x0fu;

    switch (typi) {
    case 1: {
        /* N1 SM information */
        dissect_nas5g_plain(d, ctx);
    }
    break;
    case 2: {
        // SMS
        d.add_item(d.length, &hf_pld_cont, enc::na);
        /*
        If the payload container type is set to "SMS", the payload container contents
        contain an SMS message (i.e. CP-DATA, CP-ACK or CP-ERROR) as defined in
        subclause 7.2 in 3GPP TS 24.011 [13].*/
    }
    break;
    case 4: {
        // SOR transparent container, 9.11.3.51
        /*
        If the payload container type is set to "SOR transparent container" and is
        included in the DL NAS TRANSPORT message, the payload container contents are coded
        the same way as the contents of the SOR transparent container IE (see
        subclause 9.11.3.51) for SOR data type is set to value "0" except that the first
        three octets are not included.

        If the payload container type is set to "SOR transparent container" and is
        included in the UL NAS TRANSPORT message, the payload container contents are coded
        the same way as the contents of the SOR transparent container IE (see
        subclause 9.11.3.51) for SOR data type is set to value "1" except that the first
        three octets are not included.
        */
    }
    break;
    case 3: {
        // LPP
        d.add_item(d.length, &hf_pld_cont, enc::na);
    }
    break;
    case 5: {
        /* UE policy container */
        dissect_updp(d, ctx);
    }
    break;
    case 6: {
        // UE parameters update transparent container
        /*
        If the payload container type is set to "UE parameters update transparent
        container" and is included in the DL NAS TRANSPORT message, the payload container
        contents are coded the same way as the contents of the UE parameters update
        transparent container IE (see subclause 9.11.3.53A) for UE parameters update data
        type is set to value "0" except that the first three octets are not included.

        If the payload container type is set to "UE parameters update transparent
        container" and is included in the UL NAS TRANSPORT message, the payload container
        contents are coded the same way as the contents of the UE parameters update
        transparent container IE (see subclause 9.11.3.53A) for UE parameters update data
        type is set to value "1" except that the first three octets are not included.
        */
    }
    break;
    case 15: {
        // Multiple payloads
        auto nentries = d.uint8();
        d.step(1);
        while (nentries > 0) {
            auto consumed = dissect_pld_cont_entry(d, ctx);
            d.step(consumed);
            --nentries;
        }
        /*
        If the payload container type is set to "Multiple payloads", the number of entries
        field represents the total number of payload container entries, and the payload
        container entry contents field is coded as a list of payload container entry
        according to figure 9.11.3.39.2, with each payload container entry is coded
        according to figure 9.11.3.39.3 and figure 9.11.3.39.4.*/
    }
    default:
        d.add_item(d.length, &hf_pld_cont, enc::na);
    }

    return len;
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
int mm::dissect_nas_ksi(dissector d, context* ctx) {
    use_context uc(ctx, "NAS key set identifier", d);

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
    d.add_item(d.length, &hf_element, enc::be);
    return len;
}
