#!/bin/bash

INSTALL_PATH="/opt/intel"

## Download URL for intel oneAPI toolkits
BASE_KIT_URL="https://registrationcenter-download.intel.com/akdlm/irc_nas/18236/"
BASE_KIT_SCRIPT_NAME="l_BaseKit_p_2021.4.0.3422.sh"
HPC_KIT_URL="https://registrationcenter-download.intel.com/akdlm/irc_nas/18211/"
HPC_KIT_SCRIPT_NAME="l_HPCKit_p_2021.4.0.3347.sh"

## DO NOT MODIFY
BASE_KIT_FULL_URL=$BASE_KIT_URL$BASE_KIT_SCRIPT_NAME
HPC_KIT_FULL_URL=$HPC_KIT_URL$HPC_KIT_SCRIPT_NAME

sudo mkdir -p $INSTALL_PATH && cd $INSTALL_PATH &&

echo "Downloading base kit offline installer from $BASE_KIT_FULL_URL"
sudo wget -O ./$BASE_KIT_SCRIPT_NAME $BASE_KIT_FULL_URL &&
echo "Installing MKL..."
sudo sh ./$BASE_KIT_SCRIPT_NAME -r yes -a -s --eula accept --action install --components intel.oneapi.lin.ipp.devel:intel.oneapi.lin.ippcp.devel:intel.oneapi.lin.mkl.devel &&
echo "[SUCCESS] Installed MKL."

echo "Downloading hpc kit offiline installer from $HPC_KIT_FULL_URL"
sudo wget -O ./$HPC_KIT_SCRIPT_NAME $HPC_KIT_FULL_URL &&
echo "Install ICC..."
sudo sh ./$HPC_KIT_SCRIPT_NAME  -r yes -a -s --eula accept --action install --components intel.oneapi.lin.dpcpp-cpp-compiler-pro:intel.oneapi.lin.ifort-compiler &&
echo "[SUCCESS] Installed ICC."
