#pragma once
#include "core.hh"

// dissect_msg_fnc_t
int dissect_sm_msg(packet_info* pinfo, tvbuff* buf, int offset, int len, context* = nullptr);
int dissect_mm_msg(packet_info* info, tvbuff* buf, int offset, int len, context* = nullptr);

// protocol dissect entry
int dissect_nas_5gs(packet_info* info,
                    tvbuff*      buf,
                    int          offset,
                    int          len,
                    context* = nullptr);
int dissect_nas_5gs_plain(packet_info* info,
                          tvbuff*      buf,
                          int          offset,
                          int          len,
                          context* = nullptr);
