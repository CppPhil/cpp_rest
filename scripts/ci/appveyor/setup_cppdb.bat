@echo off

REM install cppdb
svn checkout http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk "%USERPROFILE%\cppdb"

mkdir "%USERPROFILE%\cppdb\build"

cd "%USERPROFILE%\cppdb\build"

dir "C:\Program Files"

"C:\Program Files(x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"

cmake -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" -G "NMake Makefiles" ..
cmake --build .

dir "%USERPROFILE%\cppdb"
dir "%USERPROFILE%\cppdb\build"

