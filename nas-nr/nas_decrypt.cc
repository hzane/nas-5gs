#include "config.hh"

int nas_nr_decrypt(const uint8_t*       from,
                   uint8_t*             to,
                   int                  length,
                   uint8_t              type,
                   uint32_t             code,
                   uint8_t              seq,
                   nr_security_context* ctx){
    diag("in-nas-nr-decrypt\n");
    if (!is_security_type_cyphered(type)) return 0;

    if (security_ctx_is_nea0(ctx)) return 0;

    if (security_ctx_is_nea1(ctx)) {
        return nas_nr_decrypt_nea1(from, to, length, seq, ctx);
    }
    if (security_ctx_is_nea2(ctx)) {
        return nas_nr_decrypt_nea2(from, to, length, seq, ctx);
    }
    memcpy(to, from, length);
    return length;
}


bool is_security_type_cyphered(uint8_t type) { return false; }

// NEA0	空算法（也即不加密）
bool security_ctx_is_nea0(nr_security_context* ctx) { return false; }

// 	128-NEA1	128位SNOW 3G加密算法
bool security_ctx_is_nea1(nr_security_context* ctx) { return false; }

// 128-NEA2	128位AES算法
bool security_ctx_is_nea2(nr_security_context* ctx) { return false; }

// 128-NEA3	128位祖冲之算法
bool security_ctx_is_nea3(nr_security_context* ctx) { return false; }

int nas_nr_decrypt_nea1(const uint8_t*       from,
                        uint8_t*             to,
                        int                  length,
                        uint8_t              seq,
                        nr_security_context* ctx) {
    return 0;
}

int nas_nr_decrypt_nea2(const uint8_t*       from,
                        uint8_t*             to,
                        int                  length,
                        uint8_t              seq,
                        nr_security_context* ctx) {
    return 0;
}
