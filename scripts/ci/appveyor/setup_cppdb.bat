@echo off

REM install cppdb
svn checkout --quiet http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk "%USERPROFILE%\cppdb"

mkdir "%USERPROFILE%\cppdb\build"

cd "%USERPROFILE%\cppdb\build"

cmake -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" -DDISABLE_MYSQL="OFF" -DMYSQL_BACKEND_INTERNAL="OFF" -G "Visual Studio 14" ..
cmake --build .

xcopy "%USERPROFILE%\cppdb\build\Debug\cppdb.dll" "C:\cpp_rest" /Y
xcopy "%USERPROFILE%\cppdb\build\Debug\cppdb.dll" "C:\cpp_rest\Debug" /Y

dir "%USERPROFILE%\cppdb\build\Debug"

