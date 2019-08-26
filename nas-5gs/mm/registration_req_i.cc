#include "../core.hh"
#include "../dissect_mm_msg.hh"
#include "../ts24007.hh"

namespace mm_reg_req {

/* * 8.2.6 Registration request */

static const val_string nas_5gs_mm_reg_req_vals[] = {
    {0x08, "Follow-On Request bit (FOR)"},
    {0x07, "5GS registration type"},
    {0x70, "NAS key set identifier"},
    {0x80, "Type of security context flag (TSC)"},
    {0, nullptr},
};
static field_meta hfm_registration_req_flags = {
    "Message type",
    "nas_5gs.sm.message_type",
    ft::ft_uint8,
    fd::base_hex,
    nas_5gs_mm_reg_req_vals,
    nullptr,
    nullptr,
    0x0,
};

const field_meta* hf_reg_req_flags = &hfm_registration_req_flags;

static const val_string nas_5gs_mm_registration_req_elem[] = {
    {0xc0, "Non-current native NAS KSI"},
    {0x10, "5GMM capability"},
    {0x2e, "UE security capability"},
    {0x2f, "Requested NSSAI"},
    {0x52, "Last visited registered TAI"},
    {0x17, "S1 UE network capability"},
    {0x40, "Uplink data status"},
    {0x50, "PDU session status"},
    {0xb0, "MICO indication"},
    {0x2b, "UE status"},
    {0x77, "Additional GUTI"},
    {0x25, "Allowed PDU session status"},
    {0x18, "UE's usage setting"},
    {0x51, "Requested DRX parameters"},
    {0x70, "EPS NAS message container"},
    {0x74, "LADN indication"},
    {0x80, "Payload container type"},
    {0x7B, "Payload container"},
    {0x90, "Network slicing indication"},
    {0x53, "5GS update type"},
    {0x71, "NAS message container"},
    {0, nullptr},
};

/* 9.11.3.4     5GS mobile identity*/




} // namespace mm_reg_req

extern const val_string nas_5gs_mm_cause_vals[];

namespace mm {
const field_meta hfm_mm_cause = {
    "5GMM cause",
    "nas_5gs.mm.5gmm_cause",
    ft::ft_uint8,
    fd::base_dec,
    nas_5gs_mm_cause_vals,
    nullptr,
    nullptr,
    0x0,
};
const field_meta* hf_mm_cause = &hfm_mm_cause;
}

using namespace mm;
int dissect_mm_cause(dissector d, context* ctx) {
    auto cause = d.tvb->get_uint8(d.offset);
    d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_mm_cause, enc::be);
    return 1;
}


namespace mm{
/*
 * 9.9.3.21 NAS key set identifier
 */
/*
 * Type of security context flag (TSC) (octet 1)
 */
static const true_false_string nas_eps_tsc_value = {
    "Mapped security context (for KSIsgsn)",
    "Native security context (for KSIasme)",
};
const field_meta hfm_nas_eps_tsc = {
    "Type of security context flag (TSC)",
    "nas_eps.emm.tsc",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_eps_tsc_value,
    nullptr,
    0x0,
};
const field_meta* hf_nas_eps_tsc = &hfm_nas_eps_tsc;

/* NAS key set identifier (octet 1) Bits 3  2   1 */

static const val_string nas_eps_emm_NAS_key_set_identifier_vals[] = {
    {0, ""},
    {1, ""},
    {2, ""},
    {3, ""},
    {4, ""},
    {5, ""},
    {6, ""},
    {7, "No key is available"},
    {0, nullptr},
};
const field_meta hfm_nas_eps_nas_ksi = {
    "NAS key set identifier",
    "nas_eps.emm.nas_key_set_id",
    ft::ft_uint8,
    fd::base_dec,
    nas_eps_emm_NAS_key_set_identifier_vals,
    nullptr,
    nullptr,
    0x00,
};
const field_meta* hf_nas_eps_nas_ksi = &hfm_nas_eps_nas_ksi;

} // namespace mm

// nas key set id nas-key-set-id
int dissect_nas_ksi(dissector d, context* ctx) {
    auto v = d.tvb->get_uint8(d.offset);

    /* Type of security context flag (TSC) (octet 1)    V   1/2   */
    auto tsc  = (v & 0x10) >> 4;
    auto item = d.tree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_nas_eps_tsc, enc::none);
    item->set_uint(tsc, enc::be, nullptr);

    auto nas_ksi = (v & 0xe0) >> 5;
    item = d.add_item(1, hf_nas_eps_nas_ksi, enc::none);
    item->set_uint(nas_ksi, enc::be, nullptr);

    return 1;
}

const true_false_string nas_5gs_odd_even_tfs;

namespace mm {
const field_meta hf_nas_5gs_mm_odd_even = {
    "Odd/even indication",
    "nas_5gs.mm.odd_even",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    &nas_5gs_odd_even_tfs,
    nullptr,
    0x08,
};

/*
 * 9.11.3.4    5GS mobile identity
 */
static const val_string nas_5gs_mm_type_id_vals[] = {
    {0x0, "No identity"},
    {0x1, "SUCI"},
    {0x2, "5G-GUTI"},
    {0x3, "IMEI"},
    {0x4, "5G-S-TMSI"},
    {0x5, "IMEISV"},
    {0, nullptr},
};
const field_meta hf_nas_5gs_mm_type_id = {
    "Type of identity",
    "nas_5gs.mm.type_id",
    ft::ft_uint8,
    fd::base_dec,
    (nas_5gs_mm_type_id_vals),
    nullptr,
    nullptr,
    0x07,
};

static const val_string nas_5gs_mm_supi_fmt_vals[] = {
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
}

int dissect_mobile_id(dissector d, context* ctx) {
    auto len     = d.length;
    auto oct     = d.tvb->get_uint8(d.offset);
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
    case 2:{ // 5G-GUTI
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
    }break;
    case 3:{ // IMEI
        auto item = d.add_item(1, &hf_nas_5gs_mm_odd_even, enc::be);
        item = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);
        d.add_item(d.length, &hf_nas_5gs_mm_imei, enc::be);
    }break;
    case 4: {// 5G-S-TMSI
        auto item = d.add_item(1, &hf_nas_5gs_mm_odd_even, enc::be);
        item      = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);
        /* AMF Set ID */
        item = d.add_item(2, &hf_nas_5gs_amf_set_id, enc::be);
        d.step(2);         // todo: may be 1 byte
        /* AMF Pointer AMF Set ID (continued) */
        d.add_item(1, &hf_nas_5gs_amf_pointer, enc::be);
        d.add_item(4, &hf_nas_5gs_tmsi, enc::be);
    }break;
    case 5:{ // IMEISV
        auto item = d.add_item(1, &hf_nas_5gs_mm_odd_even, enc::be);
        item      = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.step(1);
        d.add_item(d.length, &hf_nas_5gs_mm_imeisv, enc::be);
    }break;
    default:{
        auto item = d.add_item(1, &hf_nas_5gs_mm_type_id, enc::none);
        item->set_uint(type_id, enc::be, nullptr);
        d.tree->add_expert(d.pinfo, d.tvb, d.offset, d.length, nullptr);
    } break;
    }
    return len;
}

/*
 *   9.11.3.44    PDU session status
 */
namespace mm{
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
}


int dissect_pdu_ses_status(dissector d, context* ctx) {
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
int dissect_nas_msg_cont(dissector d, context* ctx) {
    // TODO: implement

    /* Octets 3 to 253 contain the SMS message (i.e. CP DATA, CP ACK or CP ERROR)
     * as defined in subclause 7.2 of 3GPP TS 24.011 [10]
     */
    add_generic_msg_elem_body(d, ctx);
    return d.length;
}
