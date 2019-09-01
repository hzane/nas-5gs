#pragma once
#include "config.hh"

int dissect_gprs_timer(dissector d, context *ctx);
int dissect_gprs_timer2(dissector d, context *ctx);
int dissect_gprs_timer3(dissector d, context *ctx);
int dissect_e212_mcc_mnc(dissector d, context*); // implemented in e212_mcc_mnc.cc