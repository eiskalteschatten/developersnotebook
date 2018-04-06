.PHONY: test clean build

CXX=g++
CXXFLAGS=-Wall
BUILD_DIR=build
O_DIR=$(BUILD_DIR)/o
SRC_DIR=src
TARGET=developersnotebook.o

all:
	$(CXX) \
		./$(SRC_DIR)/*.cpp \
		`fltk-config --ldflags` \
		-o ./$(BUILD_DIR)/$(TARGET)
	chmod u+x ./$(BUILD_DIR)/$(TARGET)

clean:
	rm -f *.o 2> /dev/null
	rm -f ./$(BUILD_DIR)/$(TARGET) 2> /dev/null

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

