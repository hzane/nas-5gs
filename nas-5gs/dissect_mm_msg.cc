#include "dissect_mm_msg.hh"
#include "ts24007.hh"

using namespace nas;

extern const field_meta hf_abba = {
    "ABBA Contents",
    "nas_5gs.mm.abba_contents",
    ft::ft_uint16,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x00,
};
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


/* 9.10.2.8    S-NSSAI */
int mm::dissect_nssai(dissector d, context* ctx) {
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

    return len;
}


/*
 *   9.11.3.37    NSSAI
 */
int mm::dissect_allowed_nssai(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 0;
    while (d.length > 0) {
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, "S-NSSAI %u", i);
        d.tree       = subtree;
        auto l       = d.tvb->uint8(d.offset);
        auto item    = d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_nssai(d.slice(l), ctx);
        d.tree->set_length(consumed + 1);
        d.step(consumed);

        i++;
    }
    return len;
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
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
// todo: implement
int mm::dissect_e212_mcc_mnc(dissector d, context* ctx) { return 3; }

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
        auto subtree     = d.tree->add_subtree(
            d.pinfo, d.tvb, d.offset, -1, "Partial tracking area list  %u", num_par_tal);
        /*Head of Partial tracking area list*/
        /* Type of list    Number of elements    octet 1 */
        auto head  = d.tvb->uint8(d.offset);
        auto li    = (head & 0x60u) >> 5u;
        auto num_e = (head & 0x1fu) + 1;
        d.add_bits(flags);
        d.step(1);

        switch (li) {
        case 0: {
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            // TODO: implement
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            while (num_e > 0) {
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);

                num_e--;
            }

        } break;
        case 1: {
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);

            /*octet 5  TAC 1*/
            d.add_item(3, &hf_tac, enc::be);
            d.step(3);
        } break;
        case 2: {
            while (num_e > 0) {
                /*octet 2  MCC digit2  MCC digit1*/
                /*octet 3  MNC digit3  MCC digit3*/
                /*octet 4  MNC digit2  MNC digit1*/
                auto consumed = dissect_e212_mcc_mnc(d, ctx);
                d.step(consumed);

                /*octet 5  TAC 1*/
                d.add_item(3, &hf_tac, enc::be);
                d.step(3);

                num_e--;
            }
        } break;
        case 3: {
            auto consumed = dissect_e212_mcc_mnc(d, ctx);
            d.step(consumed);
        } break;
        default:
            d.tree->add_expert(d.pinfo, d.tvb, d.offset, d.length, nullptr);
            d.step(d.length); // consumed all left bytes
            break;
        }

        /*calculate the length of IE?*/
        subtree->set_length(d.offset - orig_offset);
        /*calculate the number of Partial tracking area list*/
        num_par_tal++;
    }
    return len;
}


/*
 *   9.11.3.46    Rejected NSSAI
 */
int mm::dissect_rej_nssai(dissector d, context* ctx) {
    bug("ie %s not dissect yet\n", "rejected NSSAI");
    return d.length;
}

/*
 *   9.11.3.37    NSSAI
 */
int mm::dissect_configured_nssai(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 1;
    while (d.length > 0) {
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "S-NSSAI %u", i);
        d.tree       = subtree;

        int length = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        auto consumed = dissect_nssai(d.slice(length), ctx);
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
        NULL,
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
        NULL,
    };
    auto orig_offset = d.offset;
    d.add_bits(psi_0_7_flags);
    d.step(1);
    d.add_bits(psi_8_15_flags);
    d.step(1);

    d.extraneous_data_check(0);
    return 2;
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


int mm::dissect_pdu_ses_react_res(dissector d, context* ctx) {

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

    d.extraneous_data_check(0);
    return 2;
}

int mm::dissect_mm_cause(dissector d, context* ctx) {
    auto cause = d.tvb->uint8(d.offset);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_mm_cause, enc::be);
    return 1;
}

/*
 *   9.11.3.30    LADN information
 */
int mm::dissect_ladn_inf(dissector d, context* ctx) {
    auto len = d.length;
    auto i   = 1;
    while (d.length > 0) {
        auto start   = d.offset;
        auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2, "LADN %u", i);
        d.tree       = subtree;
        /* DNN value (octet 5 to octet m):
         * LADN DNN value is coded as the length and value part of DNN information element
         * as specified in subclause 9.11.2.1A starting with the second octet
         */
        auto length = (int) d.tvb->uint8(d.offset);
        d.add_item(1, &hf_mm_length, enc::be);
        d.step(1);

        /* 5GS tracking area identity list (octet m+1 to octet a):
         * 5GS tracking area identity list field is coded as the length and the value part
         * of the 5GS Tracking area identity list information element as specified in
         * subclause 9.11.3.9 starting with the second octet
         */
        auto consumed = dissect_dnn(d.slice(length), ctx);
        d.step(consumed);

        d.add_item(1, &hf_mm_length, enc::be);
        d.step(consumed);

        length   = d.tvb->uint8(d.offset);
        consumed = dissect_ta_id_list(d.slice(length), ctx);
        d.step(consumed);
        subtree->set_length(d.offset - start);

        ++i;
    }
    return len;
}

/*
 *   9.11.3.31    MICO indication
 */
static const true_false_string tfs_nas_5gs_raai = {
    "all PLMN registration area allocated",
    "all PLMN registration area not allocated",
};
int mm::dissect_mico_ind(dissector d, context* ctx) {
    auto len = d.length;

    d.add_item(1, hf_nas_5gs_mm_raai_b0, enc::be);
    return 1;
}

namespace mm{
const field_meta hf_sal_al_t = {
    "Allowed type",
    "nas_5gs.mm.sal_al_t",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &tfs_nas_5gs_sal_al_t,
    nullptr,
    0x80,
};
const field_meta hf_sal_t_li = {
    "Type of list",
    "nas_5gs.mm.sal_t_li",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_sal_t_li_values,
    nullptr,
    nullptr,
    0x60,
};
} // namespace mm
// 9.11.3.49    Service area list
int mm::dissect_sal(dissector d, context* ctx) {
    auto                     len     = d.length;
    static const field_meta* flags[] = {
        &hf_sal_al_t,
        &hf_sal_t_li,
        &nas::hf_sal_num_e,
        nullptr,
    };
    auto num_par_sal = 1;
    /*Partial service area list*/
    while (d.length > 0) {
        auto start   = d.offset;
        auto subtree = d.tree->add_subtree(
            d.pinfo, d.tvb, d.offset, -1, "Partial service area list  %u", num_par_sal);
        // d.tree = subtree;
        use_tree ut(d, subtree);

        /*Head of Partial service area list*/
        /* Allowed type    Type of list    Number of elements    octet 1 */
        auto sal_head  = d.tvb->uint8(d.offset);
        auto sal_t_li  = (sal_head & 0x60) >> 5;
        auto sal_num_e = (sal_head & 0x1f) + 1;
        d.add_bits(flags);
        d.step(1);
        switch (sal_t_li) {
        case 0: {
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
        case 1: {
            /*octet 2  MCC digit2  MCC digit1*/
            /*octet 3  MNC digit3  MCC digit3*/
            /*octet 4  MNC digit2  MNC digit1*/
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);

            /*octet 5  TAC 1*/
            d.add_item(3, &hf_tac, enc::be);
            d.step(3);
        } break;
        case 2: {
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
        case 3: {
            dissect_e212_mcc_mnc(d, ctx);
            d.step(3);
        } break;
        default:
            d.tree->add_expert(d.pinfo, d.tvb, d.offset, d.length, nullptr);
            break;
        }

        /*calculate the length of IE?*/
        d.tree->set_length(d.offset - start);
        /*calculate the number of Partial service area list*/
        num_par_sal++;
    }
    return len;
}

namespace mm{
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

int mm::dissect_mobile_id(dissector d, context* ctx) {
    auto len     = d.length;
    auto oct     = d.tvb->uint8(d.offset);
    auto type_id = oct & 0x07;
    switch (type_id) {
    case 0: {
        auto item = d.tree->add_item(
            d.pinfo, d.tvb, d.offset, 1, &hf_nas_5gs_mm_odd_even, enc::be);
        item = d.tree->add_item(
            d.pinfo, d.tvb, d.offset, 1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
    } break;
    case 1: { // SUCI
        auto item =
            d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, &hf_nas_5gs_spare_b7, enc::be);
        d.add_item(1, &hf_nas_5gs_mm_supi_fmt, enc::be);
        d.add_item(1, &hf_nas_5gs_spare_b3, enc::be);
        item = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::be);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);

        auto supi_fmt = oct & 0x70;
        if (supi_fmt == 0) { // IMSI // TODO: implement
            /* MCC digit 2    MCC digit 1
             * MNC digit 3    MCC digit 3
             * MNC digit 2    MNC digit 1
             */
            add_generic_msg_elem_body(d, ctx);
        } else if (supi_fmt == 1) { // nai
            d.add_item(d.length, &hf_nas_5gs_mm_suci_nai, enc::be);
        } else {
            d.tree->add_expert(d.pinfo, d.tvb, d.offset, d.length, nullptr);
        }
    } break;
    case 2: { // 5G-GUTI
        auto item = d.tree->add_item(
            d.pinfo, d.tvb, d.offset, 1, &hf_nas_5gs_mm_odd_even, enc::be);
        item = d.tree->add_item(
            d.pinfo, d.tvb, d.offset, 1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);

        d.step(1);

        // TODO: implement
        /* MCC digit 2    MCC digit 1
         * MNC digit 3    MCC digit 3
         * MNC digit 2    MNC digit 1
         */
        /* AMF Region ID octet 7 */
        /* AMF Set ID octet 8 */
        /* AMF AMF Pointer AMF Set ID (continued) */
        add_generic_msg_elem_body(d, ctx);
    } break;
    case 3: { // IMEI
        auto item = d.add_item(1, &hf_nas_5gs_mm_odd_even, enc::be);
        item      = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);
        d.add_item(d.length, &hf_nas_5gs_mm_imei, enc::be);
    } break;
    case 4: { // 5G-S-TMSI
        auto item = d.add_item(1, &hf_nas_5gs_mm_odd_even, enc::be);
        item      = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);
        /* AMF Set ID */
        item = d.add_item(2, &hf_nas_5gs_amf_set_id, enc::be);
        d.step(2); // todo: may be 1 byte
        /* AMF Pointer AMF Set ID (continued) */
        d.add_item(1, &hf_nas_5gs_amf_pointer, enc::be);
        d.add_item(4, &hf_nas_5gs_tmsi, enc::be);
    } break;
    case 5: { // IMEISV
        auto item = d.add_item(1, &hf_nas_5gs_mm_odd_even, enc::be);
        item      = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);
        d.add_item(d.length, &hf_nas_5gs_mm_imeisv, enc::be);
    } break;
    default: {
        auto item = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.tree->add_expert(d.pinfo, d.tvb, d.offset, d.length, nullptr);
    } break;
    }
    return len;
}

/*
 *   9.11.3.39    Payload container
 */
int mm::dissect_pld_cont(dissector d, context* ctx) {
    auto len = d.length;

    auto typi = d.get_private("payload-content-type", 0);
    switch (typi) {
    case 1: { /* N1 SM information */
        dissect_nas_5gs_plain(d, ctx);
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
        &hf_nas_5gs_spare_b3,
        &hf_nas_5gs_spare_b2,
        &hf_dcni,
        &hf_nssci,
        nullptr,
    };
    return 1;
}

// nas key set id nas-key-set-id
int mm::dissect_nas_ksi(dissector d, context* ctx) {
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
