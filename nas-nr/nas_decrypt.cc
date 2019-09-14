#include "config.hh"

int nas_nr_decrypt(const uint8_t*       from,
                   uint8_t*             to,
                   int                  length,
                   uint8_t              type,
                   uint32_t             code,
                   uint8_t              seq,
                   nr_security_context* ctx){
    diag("in-nas-nr-decrypt\n");
    memcpy(to, from, length);
    return length;
}
