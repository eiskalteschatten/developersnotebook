#!/bin/bash -e

BIN_DIR=bin
TARGET_DIR_NAME=developersnotebook-0.1
TARGET_DIR=./${BIN_DIR}/${TARGET_DIR_NAME}
DEVNOTEBOOK_DIR=${TARGET_DIR}/usr/share/developersnotebook
TARGET=developersnotebook

echo " "
echo "Packaging .deb file..."
echo " "

mkdir -p ${DEVNOTEBOOK_DIR}

cp -R ./pkg/DEBIAN ${TARGET_DIR}/.
cp ./${BIN_DIR}/${TARGET} ${DEVNOTEBOOK_DIR}/.
cp ./LICENSE ${DEVNOTEBOOK_DIR}/.
cp ./README.md ${DEVNOTEBOOK_DIR}/.
cp -R ./resources/ ${DEVNOTEBOOK_DIR}/.

rm -rf ${DEVNOTEBOOK_DIR}/resources/macos

chmod +x ${DEVNOTEBOOK_DIR}/${TARGET}

cd ./${BIN_DIR}

