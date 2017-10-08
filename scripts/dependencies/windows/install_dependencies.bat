@echo off

REM install restbed
git clone --recursive https://github.com/corvusoft/restbed.git "%USERPROFILE%\restbed"
mkdir "%USERPROFILE%\restbed\build"
cd "%USERPROFILE%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO -G "Visual Studio 14" ..
msbuild /m /p:Configuration=Debug restbed.sln
msbuild /m /p:Configuration=Release restbed.sln

REM install rapidjson
git clone https://github.com/Tencent/rapidjson.git "%USERPROFILE%\rapidjson"

REM install boost

REM install GSL
git clone https://github.com/Microsoft/GSL.git "%USERPROFILE%\GSL"

REM install doctest
git clone https://github.com/onqtam/doctest.git "%USERPROFILE%\doctest"

