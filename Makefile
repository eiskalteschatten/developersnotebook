.PHONY: all test clean build bin

CXX=g++
CXXFLAGS=-Wall -g
BUILD_DIR=build
BIN_DIR=bin
SRC_DIR=src
CPPSOURCES:=$(shell find $(SRC_DIR) -type f -name *.cpp)
CPPOBJECTS:=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CPPSOURCES:.cpp=.o))
TARGET=developersnotebook
OS_TYPE:=$(shell uname)
MAC_BUNDLE=Developer\'s\ Notebook.app

ifeq ($(OS_TYPE), Darwin)

CXXINCLUDES=-I/usr/local/Cellar/gtk-mac-integration/2.0.8_2/include/gtkmacintegration/
CXXLINKED=-framework Foundation -framework Cocoa -lgtkmacintegration-gtk3.2
PKG_CONFIG_LOC=pkg-config
BUILD_RUN_TARGET=all
BUILD_RUN_OPEN=./$(BIN_DIR)/$(TARGET)
OBJCSOURCES:=$(shell find $(SRC_DIR) -type f -name *.mm)
OBJECTS:=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(OBJCSOURCES:.mm=.mm.o) $(CPPOBJECTS))

else ifeq ($(OS_TYPE), Linux)

CXXINCLUDES=
CXXLINKED=
PKG_CONFIG_LOC=pkg-config
BUILD_RUN_TARGET=all
BUILD_RUN_OPEN=./$(BIN_DIR)/$(TARGET)
OBJECTS:=$(CPPOBJECTS)

endif

# Objective C
$(BUILD_DIR)/%.mm.o: $(SRC_DIR)/%.mm
	@echo "Compiling $@...";
	@mkdir -p $(BUILD_DIR);
	@mkdir -p ${@D};
	$(CXX) \
		-o $@ \
		-c $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $@...";
	@mkdir -p $(BUILD_DIR);
	@mkdir -p ${@D};
	export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/ && \
	$(CXX) \
		$(CXXFLAGS) -std=c++11 \
		`$(PKG_CONFIG_LOC) --cflags gtk+-3.0` \
		$(CXXINCLUDES) -I ./$(SRC_DIR)/ \
		-o $@ \
		-c $<

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@echo "Linking $@...";
	@mkdir -p $(BIN_DIR);
	export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/ && \
	$(CXX) \
		$(CXXLINKED) -lsqlite3 -lboost_system -lboost_filesystem \
		`$(PKG_CONFIG_LOC) --libs gtk+-3.0` \
		-o $@ $+

all: $(BIN_DIR)/$(TARGET)
	chmod u+x ./$(BIN_DIR)/$(TARGET)

clean:
	@echo "Cleaning...";
	rm -rf ./$(BUILD_DIR)/* 2> /dev/null
	rm -rf ./$(BIN_DIR)/* 2> /dev/null

build-run-mac: create-mac-bundle
	open ./$(BIN_DIR)/$(MAC_BUNDLE)

build-run: $(BUILD_RUN_TARGET)
	$(BUILD_RUN_OPEN)

run:
	$(BUILD_RUN_OPEN)


# Install Libraries
install-libs-debian:
	sudo apt install gtk+-3.0 libsqlite3-dev libboost-all-dev

install-libs-mac:
	brew install gtk+3 gtk-mac-integration boost gdb adwaita-icon-theme


# Mac Application Bundles
create-mac-bundle: all
	bash ./scripts/create-mac-app-bundle.sh
