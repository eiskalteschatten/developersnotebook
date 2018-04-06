.PHONY: test clean build

CXX=g++
CXXFLAGS=-c -Wall
BUILD_DIR=build
O_DIR=$(BUILD_DIR)/o
SRC_DIR=src
LIB_NAME=scratchpadcore.a

$(O_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $*.cpp -o $@

$(BUILD_DIR)/$(LIB_NAME): $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)/*.cpp))
	ar rcs $@ $^

clean:
	find . -type f -name '*.o' -delete

all: $(BUILD_DIR)/$(LIB_NAME) clean

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