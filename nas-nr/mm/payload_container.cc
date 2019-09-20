#include "../dissect_mm_msg.hh"

using namespace cmn;
using namespace nas;
using namespace mm;

// Payload container  9.11.3.39
const element_meta mm::payload_container = {
    0x7B,
    "Payload container",
    dissect_payload_container,
    nullptr,
};

int mm::dissect_pld_container_entry(dissector d, context* ctx) {
    using namespace mm;
    const use_context uc(ctx, "pld-content-entry", d, -1);

    const auto len = static_cast< int >(d.ntohs());

    (void) d.add_item(1, &hf_payload_container_type, enc::be);

    uint8_t nie = (d.uint8() & 0xf0u) >> 4u;
    (void) d.add_item(1, &hf_pld_cont_entry_nie, enc::be);
    d.step(1);

    while (nie != 0) {
        const auto consumed = dissect_optional_ie(d, ctx);
        d.step(consumed);

        nie = nie - 1;
    }
    (void) d.add_item(d.length, &hf_pld_cont_entry_contents, enc::na);
    return len;
}

/*  9.11.3.39    Payload container */
int mm::dissect_payload_container(dissector d, context* ctx) {
    const use_context uc(ctx, "pld-content", d, 0);

    const auto typi = retrieve_payload_content_type(ctx) & 0x0fu;

    switch (typi) {
    case 1: {
        /* N1 SM information */
        const auto consumed = dissect_nas5g_plain(d, ctx);
        d.step(consumed);
    } break;
    case 2: {
        // SMS
        (void) d.add_item(d.length, &hf_payload_container_type, enc::na);
        d.step(d.length);
        /*
        If the payload container type is set to "SMS", the payload container contents
        contain an SMS message (i.e. CP-DATA, CP-ACK or CP-ERROR) as defined in
        subclause 7.2 in 3GPP TS 24.011 [13].*/
    } break;
    case 4: {
        // SOR transparent container, 9.11.3.51
        /*
        If the payload container type is set to "SOR transparent container" and is
        included in the DL NAS TRANSPORT message, the payload container contents are coded
        the same way as the contents of the SOR transparent container IE (see
        subclause 9.11.3.51) for SOR data type is set to value "0" except that the first
        three octets are not included.

        If the payload container type is set to "SOR transparent container" and is
        included in the UL NAS TRANSPORT message, the payload container contents are coded
        the same way as the contents of the SOR transparent container IE (see
        subclause 9.11.3.51) for SOR data type is set to value "1" except that the first
        three octets are not included.
        */
    } break;
    case 3: {
        // LPP
        (void) d.add_item(d.length, &hf_payload_container_type, enc::na);
        d.step(d.length);
    } break;
    case 5: {
        /* UE policy container */
        const auto consumed = dissect_ue_policy_delivery_procedure(d, ctx);
        d.step(consumed);
    } break;
    case 6: {
        // UE parameters update transparent container
        /*
        If the payload container type is set to "UE parameters update transparent
        container" and is included in the DL NAS TRANSPORT message, the payload container
        contents are coded the same way as the contents of the UE parameters update
        transparent container IE (see subclause 9.11.3.53A) for UE parameters update data
        type is set to value "0" except that the first three octets are not included.

        If the payload container type is set to "UE parameters update transparent
        container" and is included in the UL NAS TRANSPORT message, the payload container
        contents are coded the same way as the contents of the UE parameters update
        transparent container IE (see subclause 9.11.3.53A) for UE parameters update data
        type is set to value "1" except that the first three octets are not included.
        */
    } break;
    case 15: {
        // Multiple payloads
        auto ne = d.uint8();
        d.step(1);
        while (ne != 0) {
            const auto consumed = dissect_pld_container_entry(d, ctx);
            d.step(consumed);
            ne = ne - 1;
        }
        /*
        If the payload container type is set to "Multiple payloads", the number of entries
        field represents the total number of payload container entries, and the payload
        container entry contents field is coded as a list of payload container entry
        according to figure 9.11.3.39.2, with each payload container entry is coded
        according to figure 9.11.3.39.3 and figure 9.11.3.39.4.*/
    }
    default: {
        (void) d.add_item(d.length, &hf_payload_container_type, enc::na);
        d.step(d.length);
    }
    }

    return uc.length;
}

/* UPDP */
/* D.6.1 UE policy delivery service message type */
int mm::dissect_ue_policy_delivery_procedure(dissector d, context* ctx) {
    const use_context uc(ctx, "updp", d, 0);

    /* 9.6  Procedure transaction identity
     * Bits 1 to 8 of the third octet of every 5GSM message contain the procedure
     * transaction identity. The procedure transaction identity and its use are defined in
     * 3GPP TS 24.007
     * XXX Only 5GSM ?
     */
    (void) d.add_item(1, nas::hf_procedure_transaction_id, enc::be);
    d.step(1);

    /* Message type IE*/
    (void) d.add_item(d.length, &hf_element, enc::be);
    d.step(d.length);

    return uc.length;
}

using namespace mm;

const field_meta mm::hf_pld_cont_entry_nie = {
    "Number of optional IEs",
    "nas.nr.mm.payload_container.n_optional_ies",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0xf0u,
};
const field_meta mm::hf_pld_cont_entry_contents = {
    "Payload container entry contents",
    "nas.nr.mm.payload_container.pcec",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta mm::hf_pld_optional_ie = {
    "Optional IE",
    "nas.nr.mm.payload_container.optional_ie",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};


const value_string pld_optional_ie_type_values[] = {
    {0x12, "PDU session ID"},         // see subclause 9.11.3.41
    {0x24, "Additional information"}, // 9.11.2.1
    {0x58, "5GMM cause"},             // 9.11.3.2
    {0x37, "Back-off timer value"},   // 9.11.2.5
    {0x59, "Old PDU session ID"},     // 9.11.3.41
    {0x80, "Request type"},           // 9.11.3.47
    {0x22, "S-NSSAI"},                // 9.11.2.8
    {0x25, "DNN"},                    // 9.11.2.1A
    {0, nullptr},
};
const field_meta hf_pld_optional_ie_type = {
    "Type of Optional IE",
    "nas.nr.mm.payload_container.optional_ie.type",
    ft::ft_uint8,
    fd::base_hex,
    pld_optional_ie_type_values,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pld_optional_ie_length = {
    "Length of Optional IE",
    "nas.nr.mm.payload_container.optional_ie.length",
    ft::ft_uint8,
    fd::base_dec,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};
const field_meta hf_pld_optional_ie_value = {
    "Value of Optional IE",
    "nas.nr.mm.payload_container.optional_ie.value",
    ft::ft_bytes,
    fd::base_none,
    nullptr,
    nullptr,
    nullptr,
    0x0,
};

int mm::dissect_optional_ie(dissector d, context* ctx) {
    const use_context uc(ctx, "optional-ie", d, -1);

    const auto subtree = d.add_item(-1, &hf_pld_optional_ie, enc::na);
    use_tree   ut(d, subtree);

    (void) d.add_item(1, &hf_pld_optional_ie_type, enc::be);
    d.step(1);

    const auto len = static_cast< int >(d.uint8());
    (void) d.add_item(1, &hf_pld_optional_ie_length, enc::be);
    d.step(1);

    (void) d.add_item(len, &hf_pld_optional_ie_value, enc::na);
    subtree->set_length(d.offset - uc.offset);

    return d.offset - uc.offset;
}
