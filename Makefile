.PHONY: test clean build

CXX=g++
CXXFLAGS=-Wall
BUILD_DIR=build
SRC_DIR=src
SOURCE:=$(shell find $(SRC_DIR) -name *.cpp)
TARGET=developersnotebook
OS_TYPE:=$(shell uname)
MAC_BUNDLE=Developer\'s\ Notebook.app

ifeq ($(OS_TYPE), Darwin)
CXXINCLUDES=-I/usr/local/Cellar/gtk-mac-integration/2.0.8_2/include/gtkmacintegration/
CXXLINKED=-lgtkmacintegration-gtk3.2
else
CXXINCLUDES=
CXXLINKED=
endif

all:
	export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/ && \
	$(CXX) \
		`pkg-config --cflags gtk+-3.0` \
		$(SOURCE) \
		$(CXXINCLUDES) \
		$(CXXLINKED) \
		`pkg-config --libs gtk+-3.0` \
		-o ./$(BUILD_DIR)/$(TARGET)
	chmod u+x ./$(BUILD_DIR)/$(TARGET)

clean:
	rm -f ./$(BUILD_DIR)/$(TARGET) 2> /dev/null
	rm -rf ./$(BUILD_DIR)/$(MAC_BUNDLE) 2> /dev/null

build-run: all
	./$(BUILD_DIR)/$(TARGET)

test:
	$(CXX) \
		-lboost_unit_test_framework \
		-lboost_filesystem \
		./$(SRC_DIR)/*.cpp \
		./test/*.cpp \
		-o ./$(BUILD_DIR)/test
	chmod u+x ./$(BUILD_DIR)/test
	./$(BUILD_DIR)/test


install-libs-ubuntu:
	sudo apt install gtk+-3.0

install-libs-mac:
	brew install gtk+3 gtk-mac-integration

# Mac Application Bundles
create-mac-bundle: clean all
	mkdir -p ./$(BUILD_DIR)/$(MAC_BUNDLE)/Contents/Resources
	mkdir -p ./$(BUILD_DIR)/$(MAC_BUNDLE)/Contents/MacOS
	echo APPLnone > ./$(BUILD_DIR)/$(MAC_BUNDLE)/Contents/PkgInfo
	cp ./$(BUILD_DIR)/$(TARGET) ./$(BUILD_DIR)/$(MAC_BUNDLE)/Contents/MacOS/.
	cp ./resources/macos/Info.plist ./$(BUILD_DIR)/$(MAC_BUNDLE)/Contents/.
	cp ./resources/macos/tempicon.icns ./$(BUILD_DIR)/$(MAC_BUNDLE)/Contents/Resources/.

create-run-mac-bundle: create-mac-bundle
	open ./$(BUILD_DIR)/$(MAC_BUNDLE)
