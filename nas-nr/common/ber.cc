#include <utility>

#include "ber.hh"

#include "format.hh"
#include "use_context.hh"

inline int not_present_diag(int length, const element_meta* meta, context* ctx) {
    if (!meta || !meta->name) return length;
    if (length<=0) {
        diag("%s not present at %s\n", meta->name, paths(ctx).c_str());
    }
    return length;
}
int dissect_elem_mandatory(const element_meta* val_meta,
                                  dissector           d,
                                  tlv_fnc_t           fnc,
                                  context*            ctx) {
    auto consumed = 0;
    if (d.length > 0) {
        consumed = fnc( val_meta, d, ctx);
        d.step(consumed);
    }
    if (consumed <= 0) {
        d.add_expert(-1, formats("missing mandatory %s",  join(ctx->paths).c_str()));
        consumed = 0;
    }

    return consumed;
}

int dissect_t(const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) {
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_t, ctx);
}


int dissect_lv(const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) {
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_lv, ctx);
}
int dissect_lv_e(const element_meta* val_meta,
                             dissector           d,
                             context*            ctx) {
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_lv_e, ctx);
}
int dissect_v(const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) {
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_v, ctx);
}
int dissect_tv_short(const element_meta* val_meta,
                                 dissector           d,
                                 context*            ctx) {
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_tv_short, ctx);
}
int dissect_tv(const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) {
    unused(dissect_tv);
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_tv, ctx);
}


int dissect_tlv(const element_meta* val_meta,
                            dissector           d,
                            context*            ctx) {
    unused(dissect_tlv);
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_tlv, ctx);
}

/*  Type (T) element dissector */
int dissect_opt_t(const element_meta *val_meta,
                       dissector           d,
                       context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.uint8();
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    d.add_item(1, val_meta->name);
    d.step(1);

    return 1;
}

/* * Length Value (LV) element dissector */
int dissect_opt_lv(const element_meta *val_meta,
                        dissector           d,
                        context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto parm_len = static_cast< int >(d.uint8());

    const auto subtree = d.add_item(1 + parm_len, val_meta->name);
    const use_tree ut(d, subtree);

    // auto l = d.add_item(1, hf_gsm_a_length);
    d.step(1);

    const auto fnc = val_meta->fnc ? val_meta->fnc : dissect_unknown;

    const auto consumed = fnc(d.slice(parm_len), ctx);
    d.step(consumed);

    return parm_len + 1;
}

/* Length Value Extended(LV-E) element dissector */
int dissect_opt_lv_e(const element_meta *val_meta,
                          dissector           d,
                          context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto parm_len = d.uint16();

    const auto subtree = d.add_item(2 + parm_len, val_meta->name);
    use_tree ut(d, subtree);

    // (void) d.add_item(2, hf_gsm_e_length);
    d.step(2);

    const auto fnc      = val_meta->fnc ? val_meta->fnc : dissect_unknown;
    const auto consumed = fnc(d.slice(parm_len), ctx);
    d.step(consumed);

    return parm_len + 2;
}


/* * Value (V) element dissector
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_v(const element_meta *val_meta,
                       dissector           d,
                       context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    auto subtree = d.add_item(-1, val_meta->name);
    use_tree ut(d, subtree);

    const auto consumed = val_meta->fnc(d, ctx);
    subtree->set_length(consumed);

    return consumed;
}


/*
 * Type Value (TV) element dissector
 * Where top half nibble is IEI and bottom half nibble is value.
 *
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_tv_short(const element_meta *val_meta,
                              dissector           d,
                              context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const uint8_t iei = d.tvb->uint8(d.offset) & 0xf0u;
    if (iei != (val_meta->type & 0xf0u) && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    const auto subtree = d.add_item(1, val_meta->name);
    const use_tree ut(d, subtree);

    val_meta->fnc(d, ctx);

    return 1;
}


/*
 * Type Value (TV) element dissector
 *
 * Length cannot be used in these functions, big problem if a element dissector
 * is not defined for these.
 */
int dissect_opt_tv(const element_meta *val_meta,
                        dissector           d,
                        context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.uint8();
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    node_t subtree = nullptr;
    if (val_meta->name) {
        subtree = d.add_item(-1, val_meta->name);
        d.tree  = subtree;
    }
    d.step(1);

    const auto consumed = val_meta->fnc(d, ctx);

    if(subtree) subtree->set_length(consumed + 1);

    return consumed + 1;
}

/* Type Length Value (TLV) element dissector */
int dissect_opt_tlv(const element_meta *val_meta,
                         dissector           d,
                         context *           ctx) {
    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.uint8();
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    const auto parm_len = d.tvb->uint8(d.offset + 1);

    const auto subtree = d.add_item(parm_len + 1 + 1, val_meta->name);
    d.step(1);
    const use_tree ut(d, subtree);

    // auto t = d.add_item(1, hf_gsm_a_length);
    d.step(1);

    const auto fnc = val_meta->fnc ? val_meta->fnc : dissect_unknown;

    const auto consumed = fnc(d.slice(parm_len), ctx);
    d.step(consumed);

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
int dissect_opt_telv(const element_meta *val_meta,
                          dissector           d,
                          context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.tvb->uint8(d.offset);
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);


    uint16_t parm_len     = d.tvb->uint8(d.offset + 1);
    auto     len_length = 1;

    if ((parm_len & 0x80u) == 0) {
        /* length in 2 octets */
        parm_len     = d.tvb->uint16(d.offset + 1);
        len_length = 2;
    } else {
        parm_len = parm_len & 0x7Fu;
    }

    const auto subtree = d.add_item( parm_len + 1 + len_length, val_meta->name);
    const use_tree   ut(d, subtree);
    d.step(len_length+1);


    if (parm_len == 0) return 1 + len_length;

    const auto fnc      = val_meta->fnc ? val_meta->fnc : dissect_unknown;
    fnc(d.slice(parm_len), ctx);

    return 1 + len_length + parm_len;
}

/*
 * Type Length Value Extended(TLV-E) element dissector
 * TS 24.007
 * information elements of format LV-E or TLV-E with value part consisting of zero,
 * one or more octets and a maximum of 65535 octets (type 6).
 */
int dissect_opt_tlv_e(const element_meta *val_meta,
                           dissector           d,
                           context *           ctx) {

    if (d.length <= 0) return not_present_diag(0, val_meta, ctx);

    const auto iei = d.tvb->uint8(d.offset);
    if (iei != val_meta->type && val_meta->type != 0xffu)
        return not_present_diag(0, val_meta, ctx);

    const auto parm_len = d.tvb->uint16(d.offset + 1);

    const auto subtree = d.add_item(1 + 2 + parm_len, val_meta->name);
    const use_tree ut(d, subtree);
    d.step(1);

    // (void) d.add_item(2, hf_gsm_e_length);
    d.step(2);

    const auto fnc = val_meta->fnc ? val_meta->fnc : dissect_unknown;
    fnc(d.slice(parm_len), ctx);


    return 1 + 2 + parm_len;
}

int dissect_unknown(dissector d, context *ctx) {
    if (d.length<=0) return 0;

    const use_context uc(ctx, "unknown message body", d, -1);

    d.add_item(d.length, "Unknown", formats("%d:%d", d.offset, d.length));
    d.step(d.length);

    return uc.length;
}


int dissect_tlv_e(const element_meta* val_meta,
                  dissector           d,
                  context*            ctx) {
    return dissect_elem_mandatory( val_meta, std::move(d), dissect_opt_tlv_e, ctx);
}
