#include "core.hh"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "../def.hh"

namespace fs = std::filesystem;
using namespace std;

using buffer = vector<uint8_t> ;
using if_iterator = istreambuf_iterator<char>;

// static const uint8_t packet_sample [] = {0x7e, 0x00, 0x43};

int main() { // NOLINT: exception-escape

    string      root = "f:/nas-data";
    for(const auto& entry : fs::directory_iterator(root)) {
        auto inf = ifstream(entry, std::ios::in | std::ios::binary);
        auto buf = buffer(if_iterator(inf), if_iterator());
        tvbuff tvb = {buf.data(), static_cast< int >(buf.size())};
        context     ctx = {};
        packet_info pinfo{};
        proto_node node{};
        dissector   d{&pinfo, &node, &tvb, 0, static_cast< int >(buf.size()), nullptr};
        nas_5gs_module.dissector(d, &ctx);

        cout << entry.path() << endl;
        print_node(std::cout, &node, -1);
        cout << endl;
    }
/*
    packet_info pinfo{};
    tvbuff      tvb{packet_sample, sizeof(packet_sample)};
    proto_node  root{};
    dissector   param{&pinfo, &root, &tvb, 0, sizeof(packet_sample), nullptr};
    context     ctx = {};

    cout << nas_5gs_module.full_name << " - " << nas_5gs_module.name << endl;

    nas_5gs_module.dissector(param, &ctx);

    print_node(std::cout, &root, -1);
        */
}
