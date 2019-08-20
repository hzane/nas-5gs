#pragma once
#include "core.hh"

typedef int (*tlv_fnc_t)(const field_meta*   type_meta,
                         const element_meta* val_meta,
                         proto_node*         tree,
                         packet_info*        pinfo,
                         tvbuff*             tvb,
                         int                 offset,
                         int                 len);

inline int dissect_elem_mandary(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           proto_node*         tree,
                           packet_info*        pinfo,
                           tvbuff*             tvb,
                           int                 offset,
                           int                 len,
                           tlv_fnc_t           fnc) {
    auto consumed = 0;
    if (len > 0) {
        consumed = fnc(type_meta, val_meta, tree, pinfo, tvb, offset, len);
    }
    if (consumed <= 0) {
        tree->add_expert(pinfo,
                         tvb,
                         offset,
                         0,
                         "Missing Mandatory element %s, rest of dissection is suspect",
                         safe_str(val_meta->name));
        consumed = 0;
    }
    return consumed;
}

// * Type (T) element dissector
int        dissect_opt_elem_t(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              proto_node*         tree,
                              packet_info*        pinfo,
                              tvbuff*,
                              int offset,
                              int len);

inline int dissect_elem_t(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          proto_node*         tree,
                          packet_info*        pinfo,
                          tvbuff*             tvb,
                          int                 offset,
                          int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_t);
}

// * Length Value (LV) element dissector
int        dissect_opt_elem_lv(const field_meta*   type_meta, // == nullptr
                               const element_meta* val_meta,
                               proto_node*         tree,
                               packet_info*        pinfo,
                               tvbuff*             tvb,
                               int                 offset,
                               int                 len);

inline int dissect_elem_lv(const field_meta*   type_meta,
                        const element_meta* val_meta,
                        proto_node*         tree,
                        packet_info*        pinfo,
                        tvbuff*             tvb,
                        int                 offset,
                        int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_lv);
}

// * Length Value Extended(LV-E) element dissector
int        dissect_opt_elem_lv_e(const field_meta*   type_meta,
                                 const element_meta* val_meta,
                                 proto_node*         tree,
                                 packet_info*        pinfo,
                                 tvbuff*             tvb,
                                 int                 offset,
                                 int                 len);

inline int dissect_elem_lv_e(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             proto_node*         tree,
                             packet_info*        pinfo,
                             tvbuff*             tvb,
                             int                 offset,
                             int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_lv_e);
};

//  * Value (V) element dissector
int        dissect_opt_elem_v(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              proto_node*         tree,
                              packet_info*        pinfo,
                              tvbuff*             tvb,
                              int                 offset,
                              int                 len);

inline int dissect_elem_v(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          proto_node*         tree,
                          packet_info*        pinfo,
                          tvbuff*             tvb,
                          int                 offset,
                          int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_v);
};

// Type Value (TV) element dissector
// Where top half nibble is IEI and bottom half nibble is value.
int dissect_opt_elem_tv_short(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              proto_node*         tree,
                              packet_info*        pinfo,
                              tvbuff*             tvb,
                              int                 offset,
                              int                 len);

inline int dissect_elem_tv_short(const field_meta*   type_meta,
                                 const element_meta* val_meta,
                                 proto_node*         tree,
                                 packet_info*        pinfo,
                                 tvbuff*             tvb,
                                 int                 offset,
                                 int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_tv_short);
};

// * Type Value (TV) element dissector
int dissect_opt_elem_tv(const field_meta* type_meta,
                        const element_meta*,
                        proto_node*  tree,
                        packet_info* pinfo,
                        tvbuff*      tvg,
                        int          offset,
                        int          len);

inline int dissect_elem_tv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           proto_node*         tree,
                           packet_info*        pinfo,
                           tvbuff*             tvb,
                           int                 offset,
                           int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_tv);
};

// * Type Length Value (TLV) element dissector
int dissect_opt_elem_tlv(const field_meta*   type_meta,
                         const element_meta* val_meta,
                         proto_node*,
                         packet_info* pinfo,
                         tvbuff*,
                         int offset,
                         int len);

inline int dissect_elem_tlv(const field_meta*   type_meta,
                            const element_meta* val_meta,
                            proto_node*         tree,
                            packet_info*        pinfo,
                            tvbuff*             tvb,
                            int                 offset,
                            int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_tlv);
};

/*
 * Type Extendable Length Value (TELV) element dissector
 * This is a version where the length field can be one or two octets depending
 * if the extension bit is set or not (TS 48.016 p 10.1.2).
 *         8        7 6 5 4 3 2 1
 * octet 2 0/1 ext  length
 * octet 2a length
 */
int dissect_opt_elem_telv(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          proto_node*         tree,
                          packet_info*        pinfo,
                          tvbuff*             buf,
                          int                 offset,
                          int                 len);

inline int dissect_elem_telv(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             proto_node*         tree,
                             packet_info*        pinfo,
                             tvbuff*             tvb,
                             int                 offset,
                             int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, tvb, offset, len, dissect_opt_elem_telv);
};

/*
 * Type Length Value Extended(TLV-E) element dissector
 * TS 24.007
 * information elements of format LV-E or TLV-E with value part consisting of zero,
 * one or more octets and a maximum of 65535 octets (type 6). This category is used in EPS only.
 */
int dissect_opt_elem_tlv_e(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           proto_node*         tree,
                           packet_info*        pinfo,
                           tvbuff*             buf,
                           int                 offset,
                           int                 len);

inline int dissect_elem_tlv_e(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              proto_node*         tree,
                              packet_info*        pinfo,
                              tvbuff*             buf,
                              int                 offset,
                              int                 len) {
    return dissect_elem_mandary(
        type_meta, val_meta, tree, pinfo, buf, offset, len, dissect_opt_elem_tlv_e);
};


int add_generic_msg_elem_body(packet_info* pinfo,
                              proto_node*  tree,
                              tvbuff*      buf,
                              int          offset,
                              int          length,
                              context*     ctx);

int add_unknown(packet_info* pinfo,
                proto_node*  tree,
                tvbuff*      buf,
                int          offset,
                int          len,
                uint8_t      iet, // message type ie
                context*     ctx);
