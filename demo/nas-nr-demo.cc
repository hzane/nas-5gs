#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "../nas-nr/common/context.hh"
#include "../nas-nr/common/dissector.hh"
#include "../nas-nr/common/packet.hh"
#include "../nas-nr/nas-nr.hh"

namespace fs = std::filesystem;
using namespace std;

using buffer = vector<uint8_t> ;
using if_iterator = istreambuf_iterator<char>;

static const uint8_t packet_sample [] = {0x7e, 0x00, 0x43};



int main(int argc, char*argv[]) { // NOLINT: exception-escape
    fs::path en = argc>1 ? argv[1] : "../../data";

    for(const auto &entry : fs::directory_iterator(en)){
        cout<< endl<<entry.path()<<endl;

        auto inf = std::ifstream(entry.path(), std::ios::in | std::ios::binary);
        auto data = buffer(if_iterator(inf), if_iterator());

        packet p={};
        dissector d={&p, data.data(), (int)data.size(), 0, (int)data.size()};
        context ctx={};
        nas_message_t v={};
        de_nas_message(d, &ctx, &v);
    }
    return 0;
}
