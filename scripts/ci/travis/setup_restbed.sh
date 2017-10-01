#!/bin/bash

git clone --recursive https://github.com/corvusoft/restbed.git ~/restbed
mkdir ~/restbed/build
cd ~/restbed/build
cmake -DCMAKE_CXX_COMPILER=g++-6 -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO ..
make install

