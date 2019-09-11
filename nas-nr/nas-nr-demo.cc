#include "core.hh"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "nas-nr.hh"

namespace fs = std::filesystem;
using namespace std;

using buffer = vector<uint8_t> ;
using if_iterator = istreambuf_iterator<char>;

static const uint8_t packet_sample [] = {0x7e, 0x00, 0x43};
void dissect(const fs::path& entry) {
    auto        inf = ifstream(entry, std::ios::in | std::ios::binary);
    auto        buf = buffer(if_iterator(inf), if_iterator());
    tvbuff      tvb = {buf.data(), static_cast< int >(buf.size())};
    context     ctx = {};
    packet_info pinfo{};
    proto_node  node{};
    dissector   d{&pinfo, &node, &tvb, 0, static_cast< int >(buf.size()), nullptr};
    nas_5gs_module.dissector(d, &ctx);

    print_node(std::cout, &node, -1);
    cout << endl;
}
void print_nas_nr_message(nas_nr_message const*m) {
    if (!m) return;
    cout << string(size_t(m->indent()) * 2, ' ') << m->name() << " : " << m->value()
         << endl;
    
    print_nas_nr_message(m->first_child());
    print_nas_nr_message(m->next_sibling());
}
int main() { // NOLINT: exception-escape
    
    nas_nr_message* xroot = nullptr;
    dissect_nas_nr(&xroot, packet_sample, int(std::size(packet_sample)));
    print_nas_nr_message(xroot);
    nas_nr_message_free(xroot);

    const auto en =
        fs::path(L"f:/nas-data\\nas-1-00032348-18-7e-00-5c-00-0d-01-64.bin");
    dissect(en);

    const string root = "f:/nas-data";
    for(const auto& entry : fs::directory_iterator(root)) {
        cout << entry.path() << endl;
        dissect(entry.path());
    }
}