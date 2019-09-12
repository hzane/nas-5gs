rem execute in subdirectory nas-5gs
rem fd -e .hh -e .cc -e .cpp -e .h -x ../scc.sh {};

scc.exe -S c++17 %1 |clang-format > ../tidy/%1
