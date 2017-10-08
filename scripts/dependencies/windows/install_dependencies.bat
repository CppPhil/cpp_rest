@echo off

REM install restbed
git clone --recursive https://github.com/corvusoft/restbed.git "%USERPROFILE%\restbed"
mkdir "%USERPROFILE%\restbed\build"
cd "%USERPROFILE%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO -G "Visual Studio 15" ..
msbuild /m /p:Configuration=Debug restbed.sln
msbuild /m /p:Configuration=Release restbed.sln

REM install rapidjson
git clone https://github.com/Tencent/rapidjson.git "%USERPROFILE%\rapidjson"

REM install boost
REM create the directories
mkdir C:\Libraries
mkdir C:\Libraries\boost_1_63_0

REM download boost 1.63.0 zip file
bitsadmin.exe /transfer "boost" "https://downloads.sourceforge.net/project/boost/boost/1.63.0/boost_1_63_0.zip?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost%2F1.63.0%2F&ts=1507465780&use_mirror=netcologne" "C:\Libraries\boost_1_63_0\boost_1_63_0.zip"

REM download unzip utility
bitsadmin.exe /transfer "unzip" "http://stahlworks.com/dev/unzip.exe" "C:\Libraries\boost_1_63_0\unzip.exe"

REM unzip the .zip file into the current working directory
"C:\Libraries\boost_1_63_0\unzip.exe" "C:\Libraries\boost_1_63_0\boost_1_63_0.zip"

REM get rid of the downloaded .zip file.
DEL "C:\Libraries\boost_1_63_0\boost_1_63_0.zip"

REM get rid of the downloaded unzip utility
DEL "C:\Libraries\boost_1_63_0\unzip.exe"

REM move the unzipped boost_1_63_0 directory to where it should be.
robocopy /move /e "%cd%\boost_1_63_0" "C:\Libraries\boost_1_63_0"

REM install GSL
git clone https://github.com/Microsoft/GSL.git "%USERPROFILE%\GSL"

REM install doctest
git clone https://github.com/onqtam/doctest.git "%USERPROFILE%\doctest"

