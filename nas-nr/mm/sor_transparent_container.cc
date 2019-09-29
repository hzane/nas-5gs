#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// SOR transparent container   9.11.3.51
const element_meta mm::sor_transparent_container = {
    0x73,
    "SOR transparent container",
    dissect_sor_transparent_container,
};

using namespace cmn;
using namespace nas;

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
        (void) d.add_item(16, &hf_sor_mac_iausf);
        d.step(16);

        /* CounterSOR    octet 21-22 */
        (void) d.add_item(2, &hf_counter_sor);
        d.step(2);

        if (list_type == 0) {
            /* Secured packet    octet 23* - 2048* */
            (void) d.add_item(d.length, &hf_sor_sec_pkt);
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
        (void) d.add_item(16, &hf_sor_mac_iue);
        d.step(16);
    }

    return uc.length;
}
