#include "../common/dissect_mm_msg.hh"
#include "../common/use_context.hh"

// 9.11.3.62	Supported codec list
const tag_field hf_system_indentification = {
    "System Identification (SysID)",
    0x0,
    (const v_string[]{
        {0x0, "GSM"},
        {0x4, "UMTS"},
        {0, nullptr},
    }),
};

const uint8_field hf_bitmap_length = {
        "Bitmap Length",
        0x0,
w
};

const bool_field hf_gsm_a_dtap_codec_tdma_efr   = {{
    "TDMA EFR",
    0x80,
}};

const bool_field hf_umts_amr_2 = {{
    "UMTS AMR 2",
    0x40,
}};

const bool_field hf_umts_amr   = {{
    "UMTS AMR",
    0x20,
}};

const bool_field hf_gsm_a_dtap_codec_hr_amr     = {{
    "HR AMR",
    0x10,
}};

const bool_field hf_gsm_a_dtap_codec_fr_amr     = {{
    "FR AMR",
    0x08,
}};

const bool_field hf_gsm_a_dtap_codec_gsm_efr    = {{
    "GSM EFR",
    0x04,
}};

const bool_field hf_gsm_a_dtap_codec_gsm_hr     = {{
    "GSM HR",
    0x02,
}};

const bool_field hf_gsm_a_dtap_codec_gsm_fr     = {{
    "GSM FR",
    0x01,
}};

const bool_field hf_gsm_a_dtap_codec_umts_evs    = {{
    "UMTS EVS",
    0x40,
}};

const bool_field hf_gsm_a_dtap_codec_ohr_amr_wb  = {{
    "OHR AMR-WB",
    0x20,
}};

const bool_field hf_gsm_a_dtap_codec_ofr_amr_wb  = {{
    "OFR AMR-WB",
    0x10,
}};

const bool_field hf_gsm_a_dtap_codec_ohr_amr     = {{
    "OHR AMR",
    0x08,
}};

const bool_field hf_gsm_a_dtap_codec_umts_amr_wb = {{
    "UMTS AMR-WB",
    0x04,
}};

const bool_field hf_gsm_a_dtap_codec_fr_amr_wb   = {{
    "FR AMR-WB",
    0x02,
}};

const bool_field hf_gsm_a_dtap_codec_pdc_efr     = {{
    "PDC EFR",
    0x01,
}};


int dissect_codec_bitmap(dissector d, int idx, context* ctx) {
    const use_context uc(ctx, "codec-bitmap", d, 0);

    const auto     subtree = d.add_item(-1, formats("Codec Bitmap for SysID %u", idx));
    const use_tree ut(d, subtree);

    static const bool_field* flags1[] = {
        &hf_gsm_a_dtap_codec_tdma_efr,
        &hf_umts_amr_2,
        &hf_umts_amr,
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
        static const bool_field* flags2[] = {
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
        (void) d.add_item(&hf_system_indentification);
        d.step(1);

        const auto blen = static_cast< int >(d.uint8());
        (void) d.add_item(&hf_bitmap_length);
        d.step(1);

        if (blen > 0) {
            const auto consumed = dissect_codec_bitmap(d.slice(blen), i++, ctx);
            d.step(consumed);
        }
    }
    return uc.length;
}
