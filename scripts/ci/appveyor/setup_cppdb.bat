@echo off

REM install cppdb
svn checkout --quiet http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk "%USERPROFILE%\cppdb"

mkdir "%USERPROFILE%\cppdb\build"

cd "%USERPROFILE%\cppdb\build"

move /y "C:\cpp_rest\cppdb_windows_cmakelists\CMakeLists.txt" "%USERPROFILE%\cppdb\CMakeLists.txt"

mkdir "%USERPROFILE%\cppdb\build\Release"

xcopy "%USERPROFILE%\mysql-connector-c-6.1.11-win32\lib\libmysql.dll" "%USERPROFILE%\cppdb\build\Release" /Y

cmake -DCMAKE_PREFIX_PATH="%USERPROFILE%\mysql-connector-c-6.1.11-win32" -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" -DDISABLE_MYSQL="OFF" -DMYSQL_BACKEND_INTERNAL="ON" -DCMAKE_BUILD_TYPE="Release" -G "Visual Studio 14" ..
cmake --build .

xcopy "%USERPROFILE%\cppdb\build\Release\cppdb.dll" "C:\cpp_rest" /Y
mkdir "C:\cpp_rest\Release"
xcopy "%USERPROFILE%\cppdb\build\Release\cppdb.dll" "C:\cpp_rest\Release" /Y

