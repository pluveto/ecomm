#!/bin/bash

exit_with_error() {
    echo -e "\033[31m[ERROR]\033[0m $1"
}

rm dist/ecomm -rf
cd build
make
if [ $? -ne 0 ]; then
    exit_with_error "Failed to build."
    exit 1
fi
cp ./ecomm ../dist/
cd ../dist/
rm logs/* -rfd
source ./.env.sh
export SPDLOG_LEVEL=TRACE
./ecomm