#!/bin/bash -e

BUILD_DIR=build
BIN_DIR=bin
TARGET=developersnotebook
MAC_BUNDLE=Developer\'s\ Notebook.app
BINARY="./bin/developersnotebook"
FRAMEW_FOLDER="./bin/${MAC_BUNDLE}/Contents/Frameworks/"

function DoInstallNameTool {
    xLIB="$1"
    xLIB_NAME="$2"
    xBINARY="$3"
    echo install_name_tool -change \"${xLIB}\" \"@executable_path/../Frameworks/${xLIB_NAME}\" \"${xBINARY}\"
    install_name_tool -change ${xLIB} "@executable_path/../Frameworks/${xLIB_NAME}" "${xBINARY}"
}

echo " "
echo "Creating the Mac application bundle..."
echo " "

mkdir -p "./${BIN_DIR}/${MAC_BUNDLE}/Contents/Resources"
mkdir -p "./${BIN_DIR}/${MAC_BUNDLE}/Contents/MacOS"
mkdir -p "./${BIN_DIR}/${MAC_BUNDLE}/Contents/Frameworks"

echo APPLnone > "./${BIN_DIR}/${MAC_BUNDLE}/Contents/PkgInfo"

cp ./${BIN_DIR}/${TARGET} "./${BIN_DIR}/${MAC_BUNDLE}/Contents/MacOS/."
cp ./resources/macos/Info.plist "./${BIN_DIR}/${MAC_BUNDLE}/Contents/."
cp ./resources/macos/icon.icns "./${BIN_DIR}/${MAC_BUNDLE}/Contents/Resources/."
cp ./resources/images/* "./${BIN_DIR}/${MAC_BUNDLE}/Contents/Resources/."
cp ./resources/release-notes.html "./${BIN_DIR}/${MAC_BUNDLE}/Contents/Resources/."


# Copy shared libraries into the bundle

for LIB in $(otool -L "${BINARY}"|grep lib|cut -d '(' -f -1)
do
    echo "Handling Lib: $LIB"
    LIB_NAME=$(basename "$LIB")
    echo "    Adding ${LIB_NAME}"
    cp -Rf "${LIB}" "${FRAMEW_FOLDER}"

    DoInstallNameTool "$LIB" "$LIB_NAME" "$BINARY"
done
