/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nettle/aes.h>
#include <nettle/ctr.h>
#include <nettle/nettle-meta.h>
#include "secu_defs.h"

int nas_stream_encrypt_nea2(nas_stream_cipher_t *const stream_cipher,
                            uint8_t *const             out) {
    uint8_t  m[16];
    uint32_t local_count;
    void *   ctx;
    uint8_t *data;
    uint32_t zero_bit = 0;
    uint32_t byte_length;

    DevAssert(stream_cipher != NULL);
    DevAssert(out != NULL);
    zero_bit    = stream_cipher->blength & 0x7;
    byte_length = stream_cipher->blength >> 3;

    if (zero_bit > 0) byte_length += 1;

    ctx         = malloc(nettle_aes128.context_size);
    data        = malloc(byte_length);
    local_count = hton_int32(stream_cipher->count);
    memset(m, 0, sizeof(m));
    memcpy(&m[0], &local_count, 4);
    m[4] =
        ((stream_cipher->bearer & 0x1F) << 3) | ((stream_cipher->direction & 0x01) << 2);

    nettle_aes128.set_encrypt_key(ctx, stream_cipher->key);

    nettle_ctr_crypt(ctx,
                     nettle_aes128.encrypt,
                     nettle_aes128.block_size,
                     m,
                     byte_length,
                     data,
                     stream_cipher->message);

    if (zero_bit > 0)
        data[byte_length - 1] = data[byte_length - 1] & (uint8_t)(0xFF << (8 - zero_bit));

    memcpy(out, data, byte_length);
    free((void **) data);
    free(ctx);
    return 0;
}
