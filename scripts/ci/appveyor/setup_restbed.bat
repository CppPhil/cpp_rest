@echo off

git clone --recursive https://github.com/corvusoft/restbed.git "%USERPROFILE%\restbed"
mkdir "%USERPROFILE%\restbed\build"
cd "%USERPROFILE%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=YES -DCMAKE_BUILD_TYPE="Release" -G "Visual Studio 14" ..
msbuild /m /p:Configuration=Release restbed.sln

mkdir "C:\cpp_rest\Release"

xcopy "%USERPROFILE%\restbed\build\Release\restbed.dll" "C:\cpp_rest\Release" /Y

cd "C:\cpp_rest"

