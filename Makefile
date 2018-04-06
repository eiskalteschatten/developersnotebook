.PHONY: test clean build

CXX=g++
CXXFLAGS=-Wall
BUILD_DIR=build
O_DIR=$(BUILD_DIR)/o
SRC_DIR=src
EXE_NAME=developersnotebook.o

all:
	$(CXX) \
		./$(SRC_DIR)/*.cpp \
		`fltk-config --ldflags` \
		-o ./$(BUILD_DIR)/$(EXE_NAME)
	chmod u+x ./$(BUILD_DIR)/$(EXE_NAME)

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
	brew install boost
	cd ./lib/fltk-1.3.4-2 && make && sudo make install && make clean

