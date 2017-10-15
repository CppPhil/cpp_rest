@echo off

git clone --recursive https://github.com/corvusoft/restbed.git "%USERPROFILE%\restbed"
mkdir "%USERPROFILE%\restbed\build"
cd "%USERPROFILE%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=YES -G "Visual Studio 14" ..
msbuild /m /p:Configuration=Debug restbed.sln
cd "C:\cpp_rest"

mkdir "C:\cpp_rest\Debug"
xcopy "%USERPROFILE%\restbed\build\Debug\restbed.dll" "C:\cpp_rest\Debug" /Y

