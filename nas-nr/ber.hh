#pragma once
#include "core.hh"

struct optional_element_intra {
    bool*    presence = nullptr;
    uint8_t* t        = nullptr;
    int*     length   = nullptr;
    void*    elem     = nullptr;
};

template < typename elem_t >
struct optional_element {
    bool    presence = false;
    uint8_t t        = 0xffu;
    int     length   = 0;
    elem_t  elem     = {};

    optional_element_intra to_internal() {
        (void) this->to_internal;
        return optional_element_intra{&presence, &t, &length, &elem};
    }
};

using opt_tv_short = optional_element<uint8_t>;

inline void set_elem_presence(optional_element_intra*self, bool presence){
    if (self&&self->presence)*self->presence = presence;
}
inline void set_elem_length(optional_element_intra*self, int len){
    if (self && self->length)*self->length = len;
}
inline void set_elem_type(optional_element_intra*self, uint8_t t){
    if (self && self->t) *self->t = t;
}
inline void* get_elem_data(optional_element_intra* self) {
    return self ? self->elem : nullptr;
}

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
int dissect_opt_t(const field_meta*   type_meta,
                       const element_meta* val_meta,
                       dissector           d,
                       context*            ctx);

int dissect_t(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) ;

// * Length Value (LV) element dissector
int dissect_opt_lv(const field_meta*   type_meta, // == nullptr
                        const element_meta* val_meta,
                        dissector           d,
                        context*            ctx);

int dissect_lv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) ;

// * Length Value Extended(LV-E) element dissector
int dissect_opt_lv_e(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx);

int dissect_lv_e(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             dissector           d,
                             context*            ctx) ;

//  Value (V) element dissector
int dissect_opt_v(const field_meta*   type_meta,
                       const element_meta* val_meta,
                       dissector           d,
                       context*            ctx);

// should use val_meta->fnc directly
int dissect_v(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx) ;

// Type Value (TV) element dissector
// Where top half nibble is IEI and bottom half nibble is value.
int dissect_opt_tv_short(const field_meta*   type_meta,
                              const element_meta* val_meta,
                              dissector           d,
                              context*            ctx);

int dissect_tv_short(const field_meta*   type_meta,
                                 const element_meta* val_meta,
                                 dissector           d,
                                 context*            ctx) ;

// Type Value (TV) element dissector
int dissect_opt_tv(const field_meta* type_meta,
                        const element_meta*,
                        dissector d,
                        context*  ctx);

int dissect_tv(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx) ;

// Type Length Value (TLV) element dissector
int dissect_opt_tlv(const field_meta*   type_meta,
                         const element_meta* val_meta,
                         dissector           d,
                         context*            ctx);

int dissect_tlv(const field_meta*   type_meta,
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
int dissect_opt_telv(const field_meta*   type_meta,
                          const element_meta* val_meta,
                          dissector           d,
                          context*            ctx);

inline int dissect_telv(const field_meta*   type_meta,
                             const element_meta* val_meta,
                             dissector           d,
                             context*            ctx) {
    (void) dissect_telv;
    return dissect_elem_mandatory(type_meta, val_meta, d, dissect_opt_telv, ctx);
}

/*
 * Type Length Value Extended(TLV-E) element dissector
 * TS 24.007
 * information elements of format LV-E or TLV-E with value part consisting of zero,
 * one or more octets and a maximum of 65535 octets (type 6). This category is used in EPS
 * only.
 */
int dissect_opt_tlv_e(const field_meta*   type_meta,
                           const element_meta* val_meta,
                           dissector           d,
                           context*            ctx);

int dissect_tlv_e(const field_meta*   type_meta,
                  const element_meta* val_meta,
                  dissector           d,
                  context*            ctx);

int dissect_msg_unknown_body(dissector d, context* ctx);
