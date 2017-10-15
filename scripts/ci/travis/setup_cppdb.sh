#!/bin/bash

# install cppdb
svn checkout http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk ~/cppdb
mkdir ~/cppdb/build
cd ~/cppdb/build
cmake -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" ..
make
sudo make install
sudo cp ~/cppdb/build/libcppdb.so /usr/local/libcppdb.so
sudo cp ~/cppdb/build/libcppdb_mysql.so /usr/local/libcppdb_mysql.so
sudo cp ~/cppdb/build/libcppdb.so /usr/lib/libcppdb.so
sudo cp ~/cppdb/build/libcppdb_mysql.so /usr/lib/libcppdb_mysql.so
sudo cp ~/cppdb/build/libcppdb.so ~/build/CppPhil/cpp_rest/libcppdb.so
sudo cp ~/cppdb/build/libcppdb_mysql.so ~/build/CppPhil/cpp_rest/libcppdb_mysql.so

