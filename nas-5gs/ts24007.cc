#include "ts24007.hh"
#include "field_meta.hh"

/*
 * Type (T) element dissector
 */
int dissect_opt_elem_t(const field_meta *,
                       const element_meta *val_meta,
                       dissector           d,
                       context *           ctx) {
    if (d.length <= 0) return 0;

    auto iei = d.tvb->get_uint8(d.offset);
    if (iei != val_meta->type) return 0;

    d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 1, val_meta->name);
    // auto item = tree->add_item(pinfo, tvb, offset, 1, type_meta, enc::none);
    // item->set_uint(iei, enc::be, nullptr);

    return 1;
}


extern const field_meta *hf_gsm_a_length;

/* * Length Value (LV) element dissector */
int dissect_opt_elem_lv(const field_meta *,
                        const element_meta *val_meta,
                        dissector           d,
                        context *           ctx) {
    if (d.length <= 0) return 0;

    auto parm_len = d.tvb->get_uint8(d.offset);

    auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 1 + parm_len, val_meta->name);
    auto l = subtree->add_item(d.pinfo, d.tvb, d.offset, 1, hf_gsm_a_length, enc::none);
    l->set_uint(parm_len, enc::be, nullptr);

    if (parm_len == 0) return 1;
    auto fnc = val_meta->fnc ? val_meta->fnc : add_generic_msg_elem_body;

    d.offset      = d.offset + 1;
    d.length      = parm_len;
    d.tree        = subtree;
    auto consumed = fnc(d, ctx);
    return consumed + 1;
}

const extern field_meta *hf_gsm_e_length;

/* Length Value Extended(LV-E) element dissector */
int dissect_opt_elem_lv_e(const field_meta *,
                          const element_meta *val_meta,
                          dissector           d,
                          context *           ctx) {
    if (d.length <= 0) return 0;

    auto parm_len = d.tvb->get_ntohs(d.offset);
    auto subtree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 2 + parm_len, val_meta->name);

    auto item =
        subtree->add_item(d.pinfo, d.tvb, d.offset, 2, hf_gsm_e_length, enc::none);
    item->set_uint(parm_len, enc::be, nullptr);

    d.offset      = d.offset + 2;
    d.length      = parm_len;
    d.tree        = subtree;
    auto fnc      = val_meta->fnc ? val_meta->fnc : add_generic_msg_elem_body;
    auto consumed = fnc(d, ctx);

    return consumed + 2;
}


/* * Value (V) element dissector

 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_elem_v(const field_meta *,
                       const element_meta *val_meta,
                       dissector           d,
                       context *           ctx) {
    if (d.length <= 0) return 0;

    auto subtree  = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, val_meta->name);

    d.tree        = subtree;
    d.length      = -1;
    auto consumed = val_meta->fnc(d, ctx);
    subtree->set_length(consumed);

    return consumed;
}

static const int right_nibble = -1;
static const int left_nibble  = -2;

/*
 * Type Value (TV) element dissector
 * Where top half nibble is IEI and bottom half nibble is value.
 *
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_elem_tv_short(const field_meta *,
                              const element_meta *val_meta,
                              dissector           d,
                              context *           ctx) {
    if (d.length <= 0) return 0;

    auto iei = d.tvb->get_uint8(d.offset) & 0xF0;
    if (iei != (val_meta->type & 0xF0)) return 0;

    auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, val_meta->name);

    // auto item = subtree->add_item(pinfo, tvb, offset, 1, type_meta, enc::none);
    // item->set_uint(iei, enc::be, "0x1x-", iei >> 4);

    d.tree        = subtree;
    d.length      = right_nibble;
    auto consumed = val_meta->fnc(d, ctx);
    subtree->set_length(consumed);

    return consumed;
}


/*
 * Type Value (TV) element dissector
 *
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_elem_tv(const field_meta *,
                        const element_meta *val_meta,
                        dissector           d,
                        context *           ctx) {    
    if (d.length <= 0) return 0;

    auto iei = d.tvb->get_uint8(d.offset);
    if (iei != val_meta->type) return 0;

    auto subtree = d.tree->add_subtree(d.pinfo, d.tvb, d.offset, -1, val_meta->name);

    // auto item    = subtree->add_item(pinfo, tvb, offset, 1, type_meta, enc::none);
    // item->set_uint(iei, enc::be, nullptr);
    d.offset      = d.offset + 1;
    d.length      = -1;
    d.tree        = subtree;
    auto consumed = val_meta->fnc(d, ctx);
    subtree->set_length(consumed + 1);

    return consumed + 1;
}

/*
 * Type Length Value (TLV) element dissector
 */
int dissect_opt_elem_tlv(const field_meta *,
                         const element_meta *val_meta,
                         dissector           d,
                         context *           ctx) {
    if (d.length <= 0) return 0;

    auto iei = d.tvb->get_uint8(d.offset);
    if (iei != val_meta->type) return 0;

    auto parm_len = d.tvb->get_uint8(d.offset + 1);

    auto subtree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, parm_len + 1 + 1, val_meta->name);

    // auto item = subtree->add_item(pinfo, tvb, offset, 1, type_meta, enc::none);
    // item->set_uint(iei, enc::be, nullptr);

    auto t =
        subtree->add_item(d.pinfo, d.tvb, d.offset + 1, 1, hf_gsm_a_length, enc::none);
    t->set_uint(parm_len, enc::be, nullptr);

    if (parm_len == 0) return 2;
    d.offset      = d.offset + 2;
    d.length      = parm_len;
    d.tree        = subtree;
    auto fnc      = val_meta->fnc ? val_meta->fnc : add_generic_msg_elem_body;
    auto consumed = fnc(d, ctx);

    return consumed + 2;
}

/*
 * Type Extendable Length Value (TELV) element dissector
 * This is a version where the length field can be one or two octets depending
 * if the extension bit is set or not (TS 48.016 p 10.1.2).
 *         8        7 6 5 4 3 2 1
 * octet 2 0/1 ext  length
 * octet 2a length
 */
int dissect_opt_elem_telv(const field_meta *,
                          const element_meta *val_meta,
                          dissector           d,
                          context *           ctx) {
    if (d.length <= 0) return 0;

    auto iei = d.tvb->get_uint8(d.offset);
    if (iei != val_meta->type) return 0;

    uint16_t parm_len     = d.tvb->get_uint8(d.offset + 1);
    auto     lengt_length = 1;

    if ((parm_len & 0x80) == 0) {
        /* length in 2 octets */
        parm_len     = d.tvb->get_ntohs(d.offset + 1);
        lengt_length = 2;
    } else {
        parm_len = parm_len & 0x7F;
    }

    auto subtree = d.tree->add_subtree(
        d.pinfo, d.tvb, d.offset, parm_len + 1 + lengt_length, val_meta->name);

    // auto item = subtree->add_item(pinfo, buf, offset, 1, type_meta, enc::none);
    // item->set_uint(iei, enc::be, nullptr);

    auto item = subtree->add_item(
        d.pinfo, d.tvb, d.offset + 1, lengt_length, hf_gsm_e_length, enc::none);
    item->set_uint(parm_len, enc::be, nullptr);

    if (parm_len == 0) return 1 + lengt_length;

    d.offset      = d.offset + 1 + lengt_length;
    d.length      = parm_len;
    d.tree        = subtree;
    auto fnc      = val_meta->fnc ? val_meta->fnc : add_generic_msg_elem_body;
    auto consumed = fnc(d, ctx);

    return 1 + lengt_length + consumed;
}

/*
 * Type Length Value Extended(TLV-E) element dissector
 * TS 24.007
 * information elements of format LV-E or TLV-E with value part consisting of zero,
 * one or more octets and a maximum of 65535 octets (type 6). This category is used in EPS
 * only.
 */
int dissect_opt_elem_tlv_e(const field_meta *,
                           const element_meta *val_meta,
                           dissector           d,
                           context *           ctx) {
    if (d.length<= 0) return 0;

    auto iei = d.tvb->get_uint8(d.offset);
    if (iei != val_meta->type) return 0;

    auto parm_len = d.tvb->get_ntohs(d.offset + 1);

    auto subtree =
        d.tree->add_subtree(d.pinfo, d.tvb, d.offset, 1 + 2 + parm_len, val_meta->name);

    // auto item = subtree->add_item(pinfo, buf, offset, 1, type_meta, enc::none);
    // item->set_uint(iei, enc::be, nullptr);

    auto item =
        subtree->add_item(d.pinfo, d.tvb, d.offset + 1, 2, hf_gsm_e_length, enc::none);
    item->set_uint(parm_len, enc::be, nullptr);

    if (parm_len == 0) return 1 + 2;

    d.tree        = subtree;
    d.offset      = d.offset + 1 + 2;
    d.length      = parm_len;
    auto fnc = val_meta->fnc ? val_meta->fnc : add_generic_msg_elem_body;
    auto consumed = fnc(d, ctx);

    return 1 + 2 + consumed;
}

static field_meta const hfm_gsm_a_length = {
    "Length",
    "gsm_a.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
extern const field_meta *hf_gsm_a_length = &hfm_gsm_a_length;

static field_meta hfm_gsm_a_element_value = {
    "Element Value",
    "gsm_a.value",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const extern field_meta *hf_gsm_a_element_value = &hfm_gsm_a_element_value;

static field_meta const hfm_gsm_e_length = {
    "Length",
    "gsm_e.length",
    ft::ft_uint16,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const extern field_meta *hf_gsm_e_length = &hfm_gsm_e_length;

static field_meta const hfm_gsm_a_common_elem_id_f0 = {
    "Element ID",
    "gsm_a.common.elem_id",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
const extern field_meta *hf_gsm_a_common_elem_id_f0 = &hfm_gsm_a_common_elem_id_f0;

extern const field_meta *hf_nas_5gs_msg_elems;

int add_generic_msg_elem_body(dissector d, context *ctx) {
    d.tree->add_item(d.pinfo, d.tvb, d.offset, d.length, hf_nas_5gs_msg_elems, enc::na);
    return d.length;
}

int add_unknown(dissector d,
                uint8_t   iei, // message type ie
                context * ctx) {
    d.tree->add_expert(
        d.pinfo, d.tvb, d.offset, d.length, "Unknown Message Type %#02x", iei);
    return d.length;
}
