#!/bin/bash

git clone --recursive https://github.com/corvusoft/restbed.git ~/restbed
mkdir ~/restbed/build
cd ~/restbed/build
cmake -DBUILD_TESTS=NO -DBUILD_EXAMPLES=NO -DBUILD_SSL=NO -DBUILD_SHARED=NO ..
make install

