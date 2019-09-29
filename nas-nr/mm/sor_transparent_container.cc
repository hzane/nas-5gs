#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

using namespace cmn;
using namespace nas;

const octet_field hf_sor_mac_iue = {
    "SOR-MAC-IUE",
};
const bool_field hf_sor_hdr_ack = { // NOLINT
    "Acknowledgement (ACK)",
    0x08,
    tfs_requested_not_requested,
};
/* 9.11.3.51    SOR transparent container */
const tf_string tfs_nas_5gs_list_type = {
    "PLMN ID and access technology list",
    "Secured packet",
};

const bool_field hf_sor_hdr_list_type = {
    "List type",
    0x04,
    tfs_nas_5gs_list_type,
};

const tf_string tfs_sor_list_indication = {
    "List of preferred PLMN/access technology combinations is provided",
    "No list of preferred PLMN/access technology combinations is provided",
};

const bool_field hf_sor_hdr_list_indication = {
    "List indication",
    0x02,
    tfs_sor_list_indication,
};

const tf_string tfs_nas_5gs_sor_data_type = {
    "Carries acknowledgement of successful reception of the steering of roaming "
    "information",
    "Carries steering of roaming information",
};

const bool_field hf_sor_hdr0_sor_data_type = {
    "SOR data type",
    0x01,
    tfs_nas_5gs_sor_data_type,
};

const tf_string tfs_selected_not_selected = {"Selected", "Not Selected",};

const bool_field       hf_access_tech_utran      = {
    "Access technology UTRAN",
    0x80,
    tfs_selected_not_selected,
};

const bool_field hf_access_tech_eutran = {
    "Access technology E-UTRAN",
    0x40,
    tfs_selected_not_selected,
};


const bool_field hf_access_tech_eutran_wb = {
    "Access technology E-UTRAN in WB-S1 mode",
    0x20,
    tfs_selected_not_selected,
};
const bool_field hf_access_tech_eutran_nb = {
    "Access technology E-UTRAN in NB-S1 mode",
    0x10,
    tfs_selected_not_selected,
};
const bool_field hf_access_tech_o1_b3 = {
    "Access technology NG-RAN",
    0x08,
    tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b7 = {
    "Access technology GSM",
    0x80,
    tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b6 = {
    "Access technology GSM COMPACT",
    0x40,
    tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b5 = {
    "Access technology CDMA2000 HRPD",
    0x20,
    tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b4 = {
    "Access technology CDMA2000 1xRTT",
    0x10,
    tfs_selected_not_selected,
};

const bool_field hf_access_tech_o2_b3 = {
    "Access technology EC-GSM-IoT",
    0x08,
    tfs_selected_not_selected,
};

const bool_field hf_acces_tech_o2_b2 = {
    "Access technology GSM ",
    0x04,
    tfs_selected_not_selected,
};

const bool_field hf_rfu_b2 = {
    "Reserved for Future Use(RFU)",
    0x04,
};
const bool_field hf_rfu_b1 = {
    "Reserved for Future Use(RFU)",
    0x02,
};
const bool_field hf_rfu_b0 = {
    "Reserved for Future Use(RFU)",
    0x01,
};


const octet_field hf_sor_mac_iausf = {
    "SOR-MAC-IAUSF",
};

const uint16_field hf_counter_sor = {
    "CounterSOR",
    0x0,
};
const octet_field hf_sor_sec_pkt = {
    "Secured packet",
};

// SOR transparent container   9.11.3.51
int mm::dissect_sor_transparent_container(dissector d, context* ctx) {
    const use_context uc(ctx, "sor-transparent-container", d, 0);

    /* Layout differs depending on SOR data type*/
    static const bool_field* flags_dt0[] = {
        &hf_sor_hdr_ack,
        &hf_sor_hdr_list_type,
        &hf_sor_hdr_list_indication,
        &hf_sor_hdr0_sor_data_type,
        nullptr,
    };

    static const bool_field* flags_dt1[] = {
        &hf_sor_hdr0_sor_data_type,
        nullptr,
    };
    /* 3GPP TS 31.102 [22] subclause 4.2.5 */
    static const bool_field* flags_access_technology_1[] = {
        &hf_access_tech_utran,
        &hf_access_tech_eutran,
        &hf_access_tech_eutran_wb,
        &hf_access_tech_eutran_nb,
        &hf_access_tech_o1_b3,
        &hf_rfu_b2,
        &hf_rfu_b1,
        &hf_rfu_b0,
        nullptr,
    };

    static const bool_field* flags_access_technology_2[] = {
        &hf_access_tech_o2_b7,
        &hf_access_tech_o2_b6,
        &hf_access_tech_o2_b5,
        &hf_access_tech_o2_b4,
        &hf_access_tech_o2_b3,
        &hf_acces_tech_o2_b2,
        &hf_rfu_b1,
        &hf_rfu_b0,
        nullptr,
    };
    auto i         = 1;
    const auto oct       = d.tvb->uint8(d.offset);
    const auto data_type = oct & 0x01u;

    if (data_type == 0) {
        /* SOR header    octet 4*/
        d.add_bits(flags_dt0);
        d.step(1);

        const auto list_type = (oct & 0x4u) >> 2u;
        /* SOR-MAC-IAUSF    octet 5-20 */
        (void) d.add_item( &hf_sor_mac_iausf, 16);
        d.step(16);

        /* CounterSOR    octet 21-22 */
        (void) d.add_item( &hf_counter_sor);
        d.step(2);

        if (list_type == 0) {
            /* Secured packet    octet 23* - 2048* */
            (void) d.add_item(&hf_sor_sec_pkt, d.length);
            d.step(d.length);
        } else {
            /* PLMN ID and access technology list    octet 23*-102* */
            while (d.length > 0) {
                const auto subtree = d.add_item(-1, formats("List item %u", i));
                use_tree ut(d, subtree);
                /* The PLMN ID and access technology list consists of PLMN ID and access
                 * technology identifier and are coded as specified in 3GPP TS 31.102 [22]
                 * subclause 4.2.5 PLMN Contents:
                 * - Mobile Country Code (MCC) followed by the Mobile Network Code (MNC).
                 * Coding:
                 * - according to TS 24.008 [9].
                 */
                /* PLMN ID 1    octet 23*- 25* */
                const auto consumed = dissect_e212_mcc_mnc(d, ctx);
                d.step(consumed);

                /* access technology identifier 1    octet 26*- 27* */
                d.add_bits(flags_access_technology_1);
                d.step(1);

                d.add_bits(flags_access_technology_2);
                d.step(1);

                i++;
            }
        }
    } else { // data_type == 1
        /* SOR header    octet 4*/
        d.add_bits(flags_dt1);
        d.step(1);
        /* SOR-MAC-IUE    octet 5 - 20*/
        (void) d.add_item( &hf_sor_mac_iue, 16);
        d.step(16);
    }

    return uc.length;
}
