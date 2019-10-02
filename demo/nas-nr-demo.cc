#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "../nas-nr/nas-nr.hh"

namespace fs = std::filesystem;
using namespace std;

using buffer = vector<uint8_t> ;
using if_iterator = istreambuf_iterator<char>;

static const uint8_t packet_sample [] = {0x7e, 0x00, 0x43};



int main(int argc, char*argv[]) { // NOLINT: exception-escape
  fs::path en = argc>1 ? argv[1] : "f:/nas-data";


    return 0;
}
