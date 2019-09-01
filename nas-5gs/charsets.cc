#include "config.hh"

const uint32_t UNREP = 0x00fffd;

size_t u32utf8(uint32_t ch, uint8_t *dest) {
    if (ch < 0x80) {
        dest[0] = (char) ch;
        return 1;
    }
    if (ch < 0x800) {
        dest[0] = (ch >> 6u) | 0xC0u;
        dest[1] = (ch & 0x3Fu) | 0x80u;
        return 2;
    }
    if (ch < 0x10000) {
        dest[0] = (ch >> 12u) | 0xE0u;
        dest[1] = ((ch >> 6u) & 0x3Fu) | 0x80u;
        dest[2] = (ch & 0x3Fu) | 0x80u;
        return 3;
    }
    if (ch < 0x110000) {
        dest[0] = (ch >> 18u) | 0xF0u;
        dest[1] = ((ch >> 12u) & 0x3Fu) | 0x80u;
        dest[2] = ((ch >> 6u) & 0x3Fu) | 0x80u;
        dest[3] = (ch & 0x3Fu) | 0x80u;
        return 4;
    }
    return 0;
}

void ustring_add_utf8(ustring &s, const uint32_t c) {
    uint8_t buf[6] = {};
    
    size_t nchar = u32utf8(c, buf);
    s.insert(s.end(), buf, buf + nchar);
}

bool char_is_escape(unsigned char value) {
    static const uint8_t GN_CHAR_ESCAPE = 0x1b;
    return (value == GN_CHAR_ESCAPE);
}

uint32_t GSMe2UNICHAR(uint8_t c) {
    switch (c) {
    case 0x0a:
        return 0x0c; /* form feed */
    case 0x14:
        return '^';
    case 0x28:
        return '{';
    case 0x29:
        return '}';
    case 0x2f:
        return '\\';
    case 0x3c:
        return '[';
    case 0x3d:
        return '~';
    case 0x3e:
        return ']';
    case 0x40:
        return '|';
    case 0x65:
        return 0x20ac; /* euro */
    default:return UNREP;
    }

    return UNREP; /* invalid character */
}

/* ETSI GSM 03.38, version 6.0.1, section 6.2.1; Default alphabet */
static const uint16_t gsm_default_alphabet[0x80] = {
    '@',   0xa3,  '$',   0xa5, 0xe8,  0xe9, 0xf9,  0xec,  0xf2,  0xc7,  '\n',  0xd8,
    0xf8,  '\r',  0xc5,  0xe5, 0x394, '_',  0x3a6, 0x393, 0x39b, 0x3a9, 0x3a0, 0x3a8,
    0x3a3, 0x398, 0x39e, 0xa0, 0xc6,  0xe6, 0xdf,  0xc9,  ' ',   '!',   '\"',  '#',
    0xa4,  '%',   '&',   '\'', '(',   ')',  '*',   '+',   ',',   '-',   '.',   '/',
    '0',   '1',   '2',   '3',  '4',   '5',  '6',   '7',   '8',   '9',   ':',   ';',
    '<',   '=',   '>',   '?',  0xa1,  'A',  'B',   'C',   'D',   'E',   'F',   'G',
    'H',   'I',   'J',   'K',  'L',   'M',  'N',   'O',   'P',   'Q',   'R',   'S',
    'T',   'U',   'V',   'W',  'X',   'Y',  'Z',   0xc4,  0xd6,  0xd1,  0xdc,  0xa7,
    0xbf,  'a',   'b',   'c',  'd',   'e',  'f',   'g',   'h',   'i',   'j',   'k',
    'l',   'm',   'n',   'o',  'p',   'q',  'r',   's',   't',   'u',   'v',   'w',
    'x',   'y',   'z',   0xe4, 0xf6,  0xf1, 0xfc,  0xe0};

static uint32_t GSM2UNICHAR(uint8_t c) {
    if (c < _countof(gsm_default_alphabet)) return gsm_default_alphabet[c];

    return UNREP;
}

bool handle_ts_23_038_char(ustring &s, uint8_t code_point, bool saw_escape) {
    uint32_t uchar;

    if (char_is_escape(code_point)) {
        /*
         * XXX - if saw_escape is TRUE here, then this is
         * the case where we escape to "another extension table",
         * but TS 128 038 V11.0 doesn't specify such an extension
         * table.
         */
        saw_escape = true;
    } else {
        if (saw_escape) {
            saw_escape = false;
            uchar      = GSMe2UNICHAR(code_point);
        } else {
            uchar = GSM2UNICHAR(code_point);
        }
        ustring_add_utf8(s, uchar);
    }
    return saw_escape;
}

ustring ts_23_038_7bits_string(const uint8_t *ptr, int bit_offset, int no_of_chars) {
    if (!ptr) return ustring();

    int           char_count; /* character counter for string */
    uint8_t        in_byte, out_byte, rest = 0x00;
    const uint8_t *start_ptr  = ptr;
    bool           saw_escape = false;

    ustring ret;

    auto bits = (uint32_t)bit_offset & 0x07u;
    if (!bits) {
        bits = 7;
    }

    for (char_count = 0; char_count < no_of_chars; ptr++) {
        /* Get the next byte from the string. */
        in_byte = *ptr;

        /*
         * Combine the bits we've accumulated with bits from
         * that byte to make a 7-bit code point.
         */
        out_byte = ((in_byte & ((1u << bits) - 1u)) << (7u - bits)) | rest;

        /*
         * Leftover bits used in that code point.
         */
        rest = in_byte >> bits;

        /*
         * If we don't start from 0th bit, we shouldn't go to the
         * next char. Under *out_num we have now 0 and under Rest -
         * _first_ part of the char.
         */
        if ((start_ptr != ptr) || (bits == 7)) {
            saw_escape = handle_ts_23_038_char(ret, out_byte, saw_escape);
            char_count++;
        }

        /*
         * After reading 7 octets we have read 7 full characters
         * but we have 7 bits as well. This is the next character.
         */
        if ((bits == 1) && (char_count < no_of_chars)) {
            saw_escape = handle_ts_23_038_char(ret, rest, saw_escape);
            char_count++;
            bits = 7;
            rest = 0x00;
        } else {
            bits--;
        }
    }

    if (saw_escape) {
        /*
         * Escape not followed by anything.
         *
         * XXX - for now, show the escape as a REPLACEMENT
         * CHARACTER.
         */
        ustring_add_utf8(ret, UNREP);
    }

    return ret;
}
