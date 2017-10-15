#!/bin/bash

# install cppdb
svn checkout http://cppcms.svn.sourceforge.net/svnroot/cppcms/cppdb/trunk ~/cppdb
mkdir ~/cppdb/build
cd ~/cppdb/build
cmake -DDISABLE_SQLITE="ON" -DDISABLE_PQ="ON" -DDISABLE_ODBC="ON" ..
make
make install

