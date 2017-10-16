@echo off

git clone --recursive https://github.com/corvusoft/restbed.git "%USERPROFILE%\restbed"
mkdir "%USERPROFILE%\restbed\build"
cd "%USERPROFILE%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO -DCMAKE_BUILD_TYPE="Release" -G "Visual Studio 14" ..
msbuild /m /p:Configuration=Release restbed.sln
cd "C:\cpp_rest"

