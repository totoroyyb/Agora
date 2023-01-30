#!/bin/bash

cd `mktemp -d`
git clone --branch soapy-sdr-0.8.1 --depth 1 --single-branch https://github.com/pothosware/SoapySDR.git
cd SoapySDR
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/shared_libraries_nfs -DLIB_INSTALL_DIR:PATH=lib/x86_64-linux-gnu -DSOAPY_SDR_ROOT=/shared_libraries_nfs ../
make -j`nproc`
sudo make install
cd ../..
sudo ldconfig
