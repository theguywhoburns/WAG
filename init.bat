echo "WARNING: Should be called from VsDevCmd.bat"
mkdir build
cd build
cmake ..
devenv foo.sln /build