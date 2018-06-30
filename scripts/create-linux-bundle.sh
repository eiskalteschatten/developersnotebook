#!/bin/bash -e

BUILD_DIR=build
BIN_DIR=bin
TARGET_DIR_NAME=devnotebook
TARGET_DIR=./${BIN_DIR}/${TARGET_DIR_NAME}
TARGET=developersnotebook
BINARY="./bin/developersnotebook"

echo " "
echo "Creating the Linux bundle..."
echo " "

mkdir -p ${TARGET_DIR}

cp ./${BIN_DIR}/${TARGET} ${TARGET_DIR}/.
cp ./LICENSE ${TARGET_DIR}/.
cp ./README.md ${TARGET_DIR}/.
cp -R ./resources/ ${TARGET_DIR}/.

rm -rf ${TARGET_DIR}/resources/macos

chmod u+x ${TARGET_DIR}/${TARGET}

cd ./${BIN_DIR}

tar -zcvf linux.tar.gz ${TARGET_DIR_NAME}
