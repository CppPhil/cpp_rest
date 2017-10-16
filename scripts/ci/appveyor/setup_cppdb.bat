@echo off

REM install cppdb
svn checkout --quiet http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk "%USERPROFILE%\cppdb"

mkdir "%USERPROFILE%\cppdb\build"

cd "%USERPROFILE%\cppdb\build"

move /y "C:\cpp_rest\cppdb_windows_cmakelists\CMakeLists.txt" "%USERPROFILE%\cppdb\CMakeLists.txt"

cmake -DCMAKE_PREFIX_PATH="%USERPROFILE%\mysql-connector-c-6.1.11-winx64\lib\vs14" -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" -DDISABLE_MYSQL="OFF" -DMYSQL_BACKEND_INTERNAL="ON" -G "Visual Studio 14" ..
cmake --build .

xcopy "%USERPROFILE%\cppdb\build\Debug\cppdb.dll" "C:\cpp_rest" /Y
xcopy "%USERPROFILE%\cppdb\build\Debug\cppdb.dll" "C:\cpp_rest\Debug" /Y

