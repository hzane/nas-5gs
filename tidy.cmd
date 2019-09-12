rem execute in subdirectory nas-5gs
mkdir -p tidy/mm
mkdir -p tidy/sm
mkdir -p tidy/common

cd nas-nr
fd -e .hh -e .cc -e .cpp -e .h -x ../scc.sh {};

copy *.vcxproj ../tidy/
copy CMakeLists.txt ../tidy/

cd ..
