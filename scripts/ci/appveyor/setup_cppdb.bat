@echo off

REM download MySQL Client Library .zip file
bitsadmin.exe /transfer "MySQL Client Library" "https://dev.mysql.com/get/Downloads/Connector-C/mysql-connector-c-6.1.11-winx64.zip" "%USERPROFILE%"

REM download unzip utility
bitsadmin.exe /transfer "unzip" "http://stahlworks.com/dev/unzip.exe" "%USERPROFILE%"

REM unzip the .zip file into the current working directory
cd "%USERPROFILE%"
"%USERPROFILE%\unzip.exe" "%USERPROFILE%\mysql-connector-c-6.1.11-winx64.zip"

REM install cppdb
svn checkout --quiet http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk "%USERPROFILE%\cppdb"

mkdir "%USERPROFILE%\cppdb\build"

cd "%USERPROFILE%\cppdb\build"

cmake -DCMAKE_PREFIX_PATH="%USERPROFILE%\mysql-connector-c-6.1.11-winx64" -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" -DDISABLE_MYSQL="OFF" -DMYSQL_BACKEND_INTERNAL="ON" -G "Visual Studio 14" ..
cmake --build .

xcopy "%USERPROFILE%\cppdb\build\Debug\cppdb.dll" "C:\cpp_rest" /Y
xcopy "%USERPROFILE%\cppdb\build\Debug\cppdb.dll" "C:\cpp_rest\Debug" /Y

