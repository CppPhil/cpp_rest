@echo off

git clone --recursive https://github.com/corvusoft/restbed.git "%HOMEPATH%\restbed"
mkdir "%HOMEPATH%\restbed\build"
cd "%HOMEPATH%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO -G "Visual Studio 14" ..
msbuild /m /p:Configuration=Debug restbed.sln

