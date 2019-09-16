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

#include <string.h>
#include "secu_defs.h"

/*!
   Derive the kNASenc from kasme and perform truncate on the generated key to
   reduce his size to 128 bits. Definition of the derivation function can
   be found in 3GPP TS.33401 #A.7
   @param[in] nas_alg_type NAS algorithm distinguisher
   @param[in] nas_enc_alg_id NAS encryption/integrity algorithm identifier.
   Possible values are:
        - 0 for EIA0 algorithm (Null Integrity Protection algorithm)
        - 1 for 128-EIA1 SNOW 3G
        - 2 for 128-EIA2 AES
   @param[in] kasme Key for MME as provided by AUC
   @param[out] knas Truncated ouput key as derived by KDF
*/
