#include "dissect_mm_msg.hh"
#include "ts24007.hh"


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



extern const field_meta hf_sst = {
    "Slice/service type (SST)",
    "nas_5gs.mm.sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_sd = {
    "Slice differentiator (SD)",
    "nas_5gs.mm.mm_sd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_sst = {
    "Mapped configured SST",
    "nas_5gs.mm.mapped_conf_sst",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

const field_meta hf_mapped_conf_ssd = {
    "Mapped configured SD",
    "nas_5gs.mm.mapped_conf_ssd",
    ft::ft_uint24,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

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
        auto l       = d.tvb->get_uint8(d.offset);
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
        auto head  = d.tvb->get_uint8(d.offset);
        auto li    = (head & 0x60) >> 5;
        auto num_e = (head & 0x1f) + 1;
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

const field_meta hf_dnn = {
    "DNN",
    "nas_5gs.cmn.dnn",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
/*
 * 9.11.2.1A    DNN
 */
int mm::dissect_dnn(dissector d, context* ctx) {
    auto len = d.length;
    /* A DNN value field contains an APN as defined in 3GPP TS 23.003 */
    string str(d.safe_ptr(), d.safe_ptr() + d.safe_length(-1));
    size_t i = 0;
    while (i < str.size()) {
        auto next = str[i];
        str[i]    = '.';
        i         = i + next + 1;
    }
    /* Highlight bytes including the first length byte */
    auto item = d.add_item(len, &hf_dnn, enc::none);
    item->set_string(str);
    // d.tree->add_subtree(d.pinfo, d.tvb, d.offset, d.length, str.c_str());
    d.step(len);

    d.extraneous_data_check(0);
    return len;
}
