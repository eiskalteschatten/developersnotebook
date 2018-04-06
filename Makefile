.PHONY: test clean build

CXX=g++
CXXFLAGS=-Wall
BUILD_DIR=build
O_DIR=$(BUILD_DIR)/o
SRC_DIR=src
SOURCE:=$(shell find $(SRC_DIR) -name *.cpp)
TARGET=developersnotebook.o

all:
	$(CXX) \
		$(SOURCE) \
		`fltk-config --ldflags` \
		-o ./$(BUILD_DIR)/$(TARGET)
	chmod u+x ./$(BUILD_DIR)/$(TARGET)

clean:
	rm -f *.o 2> /dev/null
	rm -f ./$(BUILD_DIR)/$(TARGET) 2> /dev/null

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

install-libs-mac:
	brew install boost fltk

install-libs-ubuntu:
	sudo apt install fltk1.3-dev libxft-dev libxinerama-dev

