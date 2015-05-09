#!/bin/bash

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4

export OMP_NUM_THREADS=4
./cppDFT ../default.inp
