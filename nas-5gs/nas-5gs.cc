// nas-5gs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.hh"
#include <iostream>
#include "../def.hh"

using namespace std;

static const uint8_t packet_sample [] = {0x7e, 0x00, 0x43};

int main()
{
    packet_info pinfo{};
    tvbuff      tvb{packet_sample, sizeof(packet_sample)};
    proto_node  root{};
    dissector   param{&pinfo, &root, &tvb, 0, sizeof(packet_sample), nullptr};

    cout << nas_5gs_module.full_name << " - " << nas_5gs_module.name << endl;
    nas_5gs_module.dissector(param, nullptr);
    print_node(std::cout, &root, 0);
}
