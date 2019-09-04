#pragma once
#include "config.hh"
#include <algorithm>

struct tree_meta {
    const char* name;
    const char* alias;

    string pretty()const;
};

inline string tree_meta::pretty()const{
    if (alias) return string(alias);
    string ret(name);
    std::transform(ret.begin(), ret.end(), ret.begin(), [](char c)->char{
      if (isspace(c)) return '-';
        return static_cast< char >(tolower(c));
    });
    return ret;
}
