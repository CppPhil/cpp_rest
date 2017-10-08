#!/bin/bash

# install restbed
git clone --recursive https://github.com/corvusoft/restbed.git ~/restbed
mkdir ~/restbed/build
cd ~/restbed/build
cmake -DCMAKE_CXX_COMPILER=c++ -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO ..
make install

# install rapidjson
git clone https://github.com/Tencent/rapidjson.git ~/rapidjson

# install GSL
git clone https://github.com/Microsoft/GSL.git ~/GSL

# install doctest
git clone https://github.com/onqtam/doctest.git ~/doctest
