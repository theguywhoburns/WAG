@call "%VS140COMNTOOLS%VsDevCmd.bat"
mkdir build
cd build
cmake ..
devenv foo.sln /build