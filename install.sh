#!/bin/bash

cmake -B build  -DLIB_BUILD_INSTALL=ON
cd build
make install
PLcomparer