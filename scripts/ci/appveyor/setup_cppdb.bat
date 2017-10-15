@echo off

REM install cppdb
svn checkout http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk "%USERPROFILE%\cppdb"

mkdir "%USERPROFILE%\cppdb\build"

cd "%USERPROFILE%\cppdb\build"

cmake -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" -G "Visual Studio 14" ..
cmake --build .

dir "%USERPROFILE%\cppdb"
dir "%USERPROFILE%\cppdb\build"

