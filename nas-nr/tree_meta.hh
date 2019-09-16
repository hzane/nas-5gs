#pragma once
#include <algorithm>
#include "config.hh"

struct tree_meta {
    const char* name;
    const char* alias;

    string pretty()const;
};

inline char nospace(const char c){
      if (isspace(c)) return '-';
        return static_cast< char >(tolower(c));
}
inline string tree_meta::pretty() const {
    if (alias) return string(alias);
    string ret(name);
    std::transform(ret.begin(), ret.end(), ret.begin(), nospace);
    return ret;
}
