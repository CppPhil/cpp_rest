@echo off

git clone --recursive https://github.com/corvusoft/restbed.git "%USERPROFILE%\restbed"
mkdir "%USERPROFILE%\restbed\build"
cd "%USERPROFILE%\restbed\build"
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=YES -G "Visual Studio 14" ..
msbuild /m /p:Configuration=Release restbed.sln

mkdir "C:\cpp_rest\Release"

xcopy "%USERPROFILE%\restbed\build\Release\restbed.dll" "C:\cpp_rest\Release" /Y

xcopy "%USERPROFILE%\restbed\build\Release\restbed.dll" "C:\WINDOWS\System32" /Y

xcopy "%USERPROFILE%\restbed\build\Release\restbed.dll" "C:\WINDOWS\SysWoW64" /Y

ECHO ">>>>>>>>>>>!!!! HERE HERE HERE !!!!!<<<<<<<<<<"

dir "%USERPROFILE%\restbed\build"

dir "%USERPROFILE%\restbed\build\Release"

dir "%USERPROFILE%\restbed\build\Win32"

dir "%USERPROFILE%\restbed\build\Win32\Release"

