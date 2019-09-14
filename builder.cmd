REM run this script under visual studio 2008 command prompt
SET VISUAL_STUDIO_9_HOME="C:\Program Files (x86)\Microsoft Visual Studio 9.0"

cd build
cmake ../nas-nr -G "Visual Studio 9 2008"
cd ..
