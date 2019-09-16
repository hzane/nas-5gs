#include "../dissect_mm_msg.hh"

// 9.11.3.62	Supported codec list
const value_string system_id_values[] = {
    {0x0, "GSM"},
    {0x4, "UMTS"},
    {0, nullptr},
};

const field_meta hf_system_indentification = {    {
    "System Identification (SysID)",
    "gsm.sysid",
    ft::ft_uint8,
    fd::base_hex,
     system_id_values,
    nullptr,
    nullptr,
    0x0},
};

const field_meta hf_bitmap_length = {    {
        "Bitmap Length",
        "gsm.bitmap.length",
        ft::ft_uint8,
        fd::base_dec,
        nullptr,
        nullptr,
        nullptr,
        0x0,
        
    },
};

const field_meta hf_gsm_a_dtap_codec_tdma_efr   = {{
    "TDMA EFR",
    "gsm.codec.tdma.efr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x80,
}};

const field_meta hf_gsm_a_dtap_codec_umts_amr_2 = {{
    "UMTS AMR 2",
    "gsm.codec.umts.amr.2",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x40,
}};

const field_meta hf_gsm_a_dtap_codec_umts_amr   = {{
    "UMTS AMR",
    "gsm.codec.umts.amr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x20,
}};

const field_meta hf_gsm_a_dtap_codec_hr_amr     = {{
    "HR AMR",
    "gsm.codec.hr.amr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,    
    0x10,
}};

const field_meta hf_gsm_a_dtap_codec_fr_amr     = {{
    "FR AMR",
    "gsm.codec.fr.amr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x08,
}};

const field_meta hf_gsm_a_dtap_codec_gsm_efr    = {{
    "GSM EFR",
    "gsm.codec.gsm.efr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x04,
}};

const field_meta hf_gsm_a_dtap_codec_gsm_hr     = {{
    "GSM HR",
    "gsm.codec.gsm.hr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x02,
}};

const field_meta hf_gsm_a_dtap_codec_gsm_fr     = {{
    "GSM FR",
    "gsm.codec.gsm.fr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
}};

const field_meta hf_gsm_a_dtap_codec_umts_evs    = {{
    "UMTS EVS",
    "gsm.codec.umts.evs",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x40,
}};

const field_meta hf_gsm_a_dtap_codec_ohr_amr_wb  = {{
    "OHR AMR-WB",
    "gsm.codec.ohr.amr.wb",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x20,
}};

const field_meta hf_gsm_a_dtap_codec_ofr_amr_wb  = {{
    "OFR AMR-WB",
    "gsm.codec.ofr.amr.wb",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x10,
}};

const field_meta hf_gsm_a_dtap_codec_ohr_amr     = {{
    "OHR AMR",
    "gsm.codec.ohr.amr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x08,
}};

const field_meta hf_gsm_a_dtap_codec_umts_amr_wb = {{
    "UMTS AMR-WB",
    "gsm.codec.umts.amr.wb",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x04,
}};

const field_meta hf_gsm_a_dtap_codec_fr_amr_wb   = {{
    "FR AMR-WB",
    "gsm.codec.fr.amr.wb",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x02,
}};

const field_meta hf_gsm_a_dtap_codec_pdc_efr     = {{
    "PDC EFR",
    "gsm.codec.pdc.efr",
    ft::ft_boolean,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x01,
}};


int dissect_codec_bitmap(dissector d, int idx, context* ctx) {
    const use_context uc(ctx, "codec-bitmap", d, 0);

    const auto     subtree = d.add_item(-1, "Codec Bitmap for SysID %u", idx);
    const use_tree ut(d, subtree);

    static const field_meta* flags1[] = {
        &hf_gsm_a_dtap_codec_tdma_efr,
        &hf_gsm_a_dtap_codec_umts_amr_2,
        &hf_gsm_a_dtap_codec_umts_amr,
        &hf_gsm_a_dtap_codec_hr_amr,
        &hf_gsm_a_dtap_codec_fr_amr,
        &hf_gsm_a_dtap_codec_gsm_efr,
        &hf_gsm_a_dtap_codec_gsm_hr,
        &hf_gsm_a_dtap_codec_gsm_fr,
        nullptr,
    };
    d.add_bits(flags1);
    d.step(1);

    if (d.length>0) {
        static const field_meta* flags2[] = {
            &hf_gsm_a_dtap_codec_umts_evs,
            &hf_gsm_a_dtap_codec_ohr_amr_wb,
            &hf_gsm_a_dtap_codec_ofr_amr_wb,
            &hf_gsm_a_dtap_codec_ohr_amr,
            &hf_gsm_a_dtap_codec_umts_amr_wb,
            &hf_gsm_a_dtap_codec_fr_amr_wb,
            &hf_gsm_a_dtap_codec_pdc_efr,
            nullptr,
        };
        d.add_bits(flags2);
        d.step(1);
    }
    return uc.length;
}

// 9.11.3.62	Supported codec list
// See subclause 10.5.4.32 in 3GPP TS 24.008 [12].
int dissect_supported_codec_list(dissector d, context* ctx) {
    const use_context uc(ctx, "supported-codec-list", d, 0);

    auto              i = 1;
    while(d.length>0) {
        (void) d.add_item(1, &hf_system_indentification, enc::be);
        d.step(1);

        const auto blen = static_cast< int >(d.uint8());
        (void) d.add_item(1, &hf_bitmap_length, enc::be);
        d.step(1);

        if (blen > 0) {
            const auto consumed = dissect_codec_bitmap(d.slice(blen), i++, ctx);
            d.step(consumed);
        }
    }
    return uc.length;
}
