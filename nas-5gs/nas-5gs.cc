// nas-5gs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.hh"
#include <iostream>

using namespace std;

static const uint8_t packet_sample [] = {0x7e, 0x00, 0x43};

int main()
{
    packet_info pinfo{};
    tvbuff      tvb{packet_sample, sizeof(packet_sample)};
    proto_node  root{};

    cout << nas_5gs_module.full_name << " - " << nas_5gs_module.name << endl;
    nas_5gs_module.dissector(&pinfo, &root, &tvb, 0, sizeof(packet_sample), nullptr);
    print_node(std::cout, &root, 0);
}
