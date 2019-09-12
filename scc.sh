#!/usr/bin/env bash

# execute in subdirectory nas-5gs
# fd -e .hh -e .cc -x ../scc.sh {};

scc -S c++17 $1 |clang-format > ../tidy/$1
echo ../tidy/$1

# cp  *.vcxproj ../tidy/
# cp CMakeLists.txt ../tidy/
