#pragma once
#include <string>

#include "v_string.hh"

using string = std::string;

string join(const std::vector< string >& strings, const char* sep = " ");

string bits_string(const v_string* strings, uint32_t bits);

string vstring(const v_string* strings, uint32_t id, const char* missing = "Unknown");

string rstring(const range_string* strings, uint32_t id, const char* missing = "Unknown");

string bstring(uint8_t v, const char* f = nullptr, const char* t = nullptr);

using uint24_t = uint32_t;
using int24_t  = int32_t;

string istring(uint8_t v);
string istring(uint16_t v);
string istring(uint32_t v);
string i24string(uint32_t v);

string hstring(const uint8_t* data,
               int            len,
               const char*    sep = nullptr,
               const char*    lf  = nullptr);

string bitstring(const uint8_t* data, int bits, const char* sep = nullptr);

string gmt_string(const uint8_t* d);
string utc_string(const uint8_t* d, int length);
string gsm7_string(const uint8_t* gsm, int len);
string ambr_string(const uint8_t* d, int length);

//  [3] 10.5.1.13 PLMN list TS24.008
string mcc_string(const uint8_t* d, int length = 3);
string mnc_string(const uint8_t* d, int length = 3);
// BCD number
string bcd_string(const uint8_t* d, int length);
string imei_string(const uint8_t* d, int length); // 0xf0 terminated if even

string ipv6_link_local_string(const uint8_t* d, int length);

string apn_string(const uint8_t* d, int len);

string gprs_timer_string(uint8_t d);
string gprs_timer_2_string(uint8_t d);
string gprs_timer_3_string(uint8_t d);

uint8_t  umask(uint8_t v, uint8_t mask);
uint16_t u16mask(uint16_t v, uint16_t mask);
uint24_t u24mask(uint24_t v, uint24_t mask);
uint32_t u32mask(uint32_t v, uint32_t mask);
