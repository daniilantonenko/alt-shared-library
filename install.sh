#!/bin/bash

mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=1 ..
make
make install