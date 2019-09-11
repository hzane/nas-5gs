#include "ber.hh"
#include "dissect_nas5g.hh"
#include "field_meta.hh"

inline int not_present_diag(int length, const element_meta* meta, context* ctx) {
    if (!meta || !meta->name) return length;
    if (length<=0) {
        diag("%s not present at %s\n", meta->name, paths(ctx).c_str());
    }
    return length;
}
int dissect_elem_mandatory(const field_meta*   type_meta,
                                  const element_meta* val_meta,
                                  dissector           d,
                                  tlv_fnc_t           fnc,
                                  context*            ctx) {
    auto consumed = 0;
    if (d.length > 0) {
        consumed = fnc(type_meta, val_meta, d, ctx);
        d.step(consumed);
    }
    if (consumed <= 0) {
        diag("Missing Mandatory element %s, rest of dissection is suspect %s\n",
             paths(ctx).c_str(), val_meta->name);
        consumed = 0;
    }

    return consumed;
}

int dissect_t(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) {
    unused(dissect_t);
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_t, ctx);
}


int dissect_lv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) {
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_lv, ctx);
}
int dissect_lv_e(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             dissector           d,
                             context*            ctx) {
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_lv_e, ctx);
}
int dissect_v(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) {
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_v, ctx);
}
int dissect_tv_short(const field_meta*   type_meta,
                                 const element_meta* val_meta,
                                 dissector           d,
                                 context*            ctx) {
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_tv_short, ctx);
}
int dissect_tv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) {
    unused(dissect_tv);
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_tv, ctx);
}


int dissect_tlv(const field_meta*   type_meta,
                            const element_meta* val_meta,
                            dissector           d,
                            context*            ctx) {
    unused(dissect_tlv);
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_tlv, ctx);
}

/*  Type (T) element dissector */
int dissect_opt_t(const field_meta *,
                       const element_meta *val_meta,
                       dissector           d,
                       context *           ctx) {
    (void) ctx;
    const auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.uint8();
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    set_elem_presence(e, true);
    set_elem_type(e, iei);

    d.add_item(1, val_meta->name);
    d.step(1);

    return 1;
}


// extern const field_meta *hf_gsm_a_length;

/* * Length Value (LV) element dissector */
int dissect_opt_lv(const field_meta *,
                        const element_meta *val_meta,
                        dissector           d,
                        context *           ctx) {
    auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e,false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);
    set_elem_presence(e, true);

    const auto parm_len = static_cast< int >(d.uint8());
    set_elem_length(e, parm_len);

    const auto subtree = d.add_item(1 + parm_len, val_meta->name);
    const use_tree ut(d, subtree);

    // auto l = d.add_item(1, hf_gsm_a_length, enc::be);
    d.step(1);

    if (parm_len == 0) return 1;
    const auto fnc = val_meta->fnc ? val_meta->fnc : dissect_msg_unknown_body;

    const auto consumed = fnc(d.slice(parm_len).use_elem(e ? e->elem : nullptr), ctx);
    d.step(consumed);

    return parm_len + 1;
}

// const extern field_meta *hf_gsm_e_length;

/* Length Value Extended(LV-E) element dissector */
int dissect_opt_lv_e(const field_meta *,
                          const element_meta *val_meta,
                          dissector           d,
                          context *           ctx) {
    auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto parm_len = d.ntohs();
    set_elem_presence(e, true);
    set_elem_length(e, parm_len);

    const auto subtree = d.add_item(2 + parm_len, val_meta->name);
    use_tree ut(d, subtree);

    // (void) d.add_item(2, hf_gsm_e_length, enc::be);
    d.step(2);

    const auto fnc      = val_meta->fnc ? val_meta->fnc : dissect_msg_unknown_body;
    const auto consumed = fnc(d.slice(parm_len).use_elem(get_elem_data(e)), ctx);
    d.step(consumed);

    return parm_len + 2;
}


/* * Value (V) element dissector

 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_v(const field_meta *,
                       const element_meta *val_meta,
                       dissector           d,
                       context *           ctx) {
    auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    auto subtree = d.add_item(-1, val_meta->name);
    use_tree ut(d, subtree);

    const auto consumed = val_meta->fnc(d, ctx);
    subtree->set_length(consumed);

    set_elem_presence(e, consumed>0);
    set_elem_length(e, consumed);

    return consumed;
}


/*
 * Type Value (TV) element dissector
 * Where top half nibble is IEI and bottom half nibble is value.
 *
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_tv_short(const field_meta *,
                              const element_meta *val_meta,
                              dissector           d,
                              context *           ctx) {
    const auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const uint8_t iei = d.tvb->uint8(d.offset) & 0xf0u;
    if (iei != (val_meta->type & 0xf0u) && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    set_elem_presence(e, true);
    set_elem_type(e, iei);

    const auto subtree = d.add_item(1, val_meta->name);
    const use_tree ut(d, subtree);

    const auto consumed = val_meta->fnc(d.use_elem(get_elem_data(e)), ctx);
    unused(consumed);

    return 1;
}


/*
 * Type Value (TV) element dissector
 *
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_tv(const field_meta *,
                        const element_meta *val_meta,
                        dissector           d,
                        context *           ctx) {
    const auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.uint8();
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    set_elem_presence(e, true);
    set_elem_type(e, iei);

    proto_node* subtree = nullptr;
    if (val_meta->name) {
        subtree = d.add_item(-1, val_meta->name);
        const use_tree ut(d, subtree);
    }
    d.step(1);

    const auto consumed = val_meta->fnc(d.use_elem(get_elem_data(e)), ctx);

    if(subtree) subtree->set_length(consumed + 1);
    set_elem_length(e, consumed);

    return consumed + 1;
}

/* Type Length Value (TLV) element dissector */
int dissect_opt_tlv(const field_meta *,
                         const element_meta *val_meta,
                         dissector           d,
                         context *           ctx) {
    const auto e = static_cast< optional_element_intra* >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.uint8();
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    set_elem_presence(e, true);
    set_elem_type(e, iei);

    const auto parm_len = d.tvb->uint8(d.offset + 1);

    const auto subtree = d.add_item(parm_len + 1 + 1, val_meta->name);
    d.step(1);
    const use_tree ut(d, subtree);

    // auto t = d.add_item(1, hf_gsm_a_length, enc::be);
    d.step(1);

    if (parm_len == 0) return 2;

    const auto fnc = val_meta->fnc ? val_meta->fnc : dissect_msg_unknown_body;

    const auto consumed = fnc(d.slice(parm_len).use_elem(get_elem_data(e)), ctx);
    d.step(consumed);
    set_elem_length(e, consumed);

    return parm_len + 2;
}



/*
 * Type Extendable Length Value (TELV) element dissector
 * This is a version where the length field can be one or two octets depending
 * if the extension bit is set or not (TS 48.016 p 10.1.2).
 *         8        7 6 5 4 3 2 1
 * octet 2 0/1 ext  length
 * octet 2a length
 */
int dissect_opt_telv(const field_meta *,
                          const element_meta *val_meta,
                          dissector           d,
                          context *           ctx) {
    auto e = static_cast< optional_element_intra * >(d.data);
    set_elem_presence(e, false);

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.tvb->uint8(d.offset);
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    set_elem_presence(e, true);
    set_elem_type(e, iei);

    uint16_t parm_len     = d.tvb->uint8(d.offset + 1);
    auto     lengt_length = 1;

    if ((parm_len & 0x80u) == 0) {
        /* length in 2 octets */
        parm_len     = d.tvb->ntohs(d.offset + 1);
        lengt_length = 2;
    } else {
        parm_len = parm_len & 0x7Fu;
    }

    const auto subtree = d.add_item( parm_len + 1 + lengt_length, val_meta->name);
    const use_tree   ut(d, subtree);
    d.step(1);

    // (void) d.add_item(lengt_length, hf_gsm_e_length, enc::none);
    d.step(lengt_length);


    if (parm_len == 0) return 1 + lengt_length;

    const auto fnc      = val_meta->fnc ? val_meta->fnc : dissect_msg_unknown_body;
    const auto consumed = fnc(d.slice(parm_len).use_elem(get_elem_data(e)), ctx);

    set_elem_length(e, consumed);

    return 1 + lengt_length + consumed;
}

/*
 * Type Length Value Extended(TLV-E) element dissector
 * TS 24.007
 * information elements of format LV-E or TLV-E with value part consisting of zero,
 * one or more octets and a maximum of 65535 octets (type 6). This category is used in EPS
 * only.
 */
int dissect_opt_tlv_e(const field_meta *,
                           const element_meta *val_meta,
                           dissector           d,
                           context *           ctx) {
    auto e = static_cast< optional_element_intra* >(d.data);
    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.tvb->uint8(d.offset);
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    set_elem_presence(e, true);
    set_elem_type(e, iei);

    const auto parm_len = d.tvb->ntohs(d.offset + 1);

    const auto subtree = d.add_item(1 + 2 + parm_len, val_meta->name);
    const use_tree ut(d, subtree);
    d.step(1);

    // (void) d.add_item(2, hf_gsm_e_length, enc::be);
    d.step(2);

    if (parm_len == 0) return 1 + 2;

    const auto fnc = val_meta->fnc ? val_meta->fnc : dissect_msg_unknown_body;
    const auto consumed = fnc(d.slice(parm_len).use_elem(get_elem_data(e)), ctx);

    set_elem_length(e, consumed);

    return 1 + 2 + consumed;
}
#if 0
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
const field_meta *hf_gsm_a_length = &hfm_gsm_a_length;
#endif

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
const field_meta *hf_gsm_a_element_value = &hfm_gsm_a_element_value;

#if 0
static field_meta const hfm_gsm_e_length = {
    "Length",
    "gsm.length",
    ft::ft_bytes,
    fd::extl,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta *hf_gsm_e_length = &hfm_gsm_e_length;
#endif

const field_meta hfm_gsm_a_common_elem_id_f0 = {
    "Element ID",
    "gsm_a.common.elem_id",
    ft::ft_uint8,
    fd::base_hex,
    nullptr,
    nullptr,
    nullptr,
    0xf0,
};
const field_meta *hf_gsm_a_common_elem_id_f0 = &hfm_gsm_a_common_elem_id_f0;

int dissect_msg_unknown_body(dissector d, context *ctx) {
    const use_context uc(ctx, "unknown message body", d, -1);

    d.tree->add_item(d.pinfo, d.tvb, d.offset, d.length, nas::hf_msg_elem, enc::na);
    return d.length;
}
