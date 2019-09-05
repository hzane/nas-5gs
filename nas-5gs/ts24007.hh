#pragma once
#include "core.hh"

struct opt_elem {
    bool*    presence;
    uint8_t* t;
    int*     length;
    void*    elem;
};

template < typename elem_t >
struct opt_element {
    bool    presence;
    uint8_t t;
    int     length;
    elem_t  elem;

    opt_elem to_internal() { return opt_elem{&presence, &t, &length, &elem}; }
};

inline void set_elem_presence(opt_elem*self, bool presence){
    if (self&&self->presence)*self->presence = presence;
}
inline void set_elem_length(opt_elem*self, int len){
    if (self && self->length)*self->length = len;
}
inline void set_elem_type(opt_elem*self, uint8_t t){
    if (self && self->t) *self->t = t;
}
inline void* get_elem_data(opt_elem* self) { return self ? self->elem : nullptr; }

typedef int (*tlv_fnc_t)(const field_meta*   type_meta,
                         const element_meta* val_meta,
                         dissector           d,
                         context*            ctx);

int dissect_elem_mandatory(const field_meta*   type_meta,
                                const element_meta* val_meta,
                                dissector           d,
                                tlv_fnc_t           fnc,
                                context*            ctx) ;

// * Type (T) element dissector
int dissect_opt_elem_t(const field_meta*   type_meta,
                       const element_meta* val_meta,
                       dissector           d,
                       context*            ctx);

int dissect_elem_t(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) ;

// * Length Value (LV) element dissector
int dissect_opt_elem_lv(const field_meta*   type_meta, // == nullptr
                        const element_meta* val_meta,
                        dissector           d,
                        context*            ctx);

int dissect_elem_lv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) ;

// * Length Value Extended(LV-E) element dissector
int dissect_opt_elem_lv_e(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx);

int dissect_elem_lv_e(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             dissector           d,
                             context*            ctx) ;

//  Value (V) element dissector
int dissect_opt_elem_v(const field_meta*   type_meta,
                       const element_meta* val_meta,
                       dissector           d,
                       context*            ctx);

// should use val_meta->fnc directly
int dissect_elem_v(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) ;

// Type Value (TV) element dissector
// Where top half nibble is IEI and bottom half nibble is value.
int dissect_opt_elem_tv_short(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              dissector           d,
                              context*            ctx);

int dissect_elem_tv_short(const field_meta*   type_meta,
                                 const element_meta* val_meta,
                                 dissector           d,
                                 context*            ctx) ;

// Type Value (TV) element dissector
int dissect_opt_elem_tv(const field_meta* type_meta,
                        const element_meta*,
                        dissector d,
                        context*  ctx);

int dissect_elem_tv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) ;

// Type Length Value (TLV) element dissector
int dissect_opt_elem_tlv(const field_meta*   type_meta,
                         const element_meta* val_meta,
                         dissector           d,
                         context*            ctx);

int dissect_elem_tlv(const field_meta*   type_meta,
                            const element_meta* val_meta,
                            dissector           d,
                            context*            ctx) ;

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
                          dissector           d,
                          context*            ctx);

inline int dissect_elem_telv(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             dissector           d,
                             context*            ctx) {
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_elem_telv, ctx);
};

/*
 * Type Length Value Extended(TLV-E) element dissector
 * TS 24.007
 * information elements of format LV-E or TLV-E with value part consisting of zero,
 * one or more octets and a maximum of 65535 octets (type 6). This category is used in EPS
 * only.
 */
int dissect_opt_elem_tlv_e(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx);

inline int dissect_elem_tlv_e(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              dissector           d,
                              context*            ctx) {
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_elem_tlv_e, ctx);
};

int dissect_msg_unknown_body(dissector d, context* ctx);
