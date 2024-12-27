
# Settings
OPTIMIZE := false
OPT_FLAG := O2

DEBUG := true
DEBUG_MACRO := DEBUG

ANALYZE := false
ANALYZE_FLAG := analyze

APP_NAME := hello_triangle

# Compiling
CXX := clang++

LDFLAGS := -lglfw
CXXFLAGS := -std=c++17

ifeq ($(DEBUG), true)
	CXXFLAGS += -D$(DEBUG_MACRO)
	ifeq ($(ANALYZE), true)
		CXXFLAGS += --$(ANALYZE_FLAG)
		LDFLAGS += --$(ANALYZE_FLAG)
	endif
endif

ifeq ($(OPTIMIZE), true)
	LDFLAGS += -$(OPT_FLAG)
endif

# Directories
BUILD := build
DEP := dep
SRC := src

# Engine paths
ENGINE := $(SRC)/Engine

# GLFW paths
GLFW_PAHT := $(DEP)/glfw
GLFW_INCLUDE_PATH := $(GLFW_PAHT)/include
GLFW_LIB_PATH := $(GLFW_PAHT)/lib

# GLAD paths
GLAD_PATH := $(DEP)/glad

INCLUDE := -I$(GLFW_INCLUDE_PATH) -I$(GLAD_PATH) -I$(SRC)
LIBS :=  -L$(GLFW_LIB_PATH)

SRC_FILES := $(shell find $(SRC) -name '*.cpp')
FILES := $(patsubst %.cpp, $(BUILD)/%.o, $(notdir $(SRC_FILES))) $(BUILD)/main.o

all: build

libs:
	cd $(GLAD_PATH) && $(CXX) -o glad.o -Iinclude -c glad.c    # && ar -rc glad.a glad.o

build: $(APP_NAME)

$(APP_NAME): $(FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(GLAD_PATH)/glad.o $(INCLUDE) $(LIBS)

$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

$(BUILD)/%.o: $(SRC)/**/%.cpp $(SRC)/**/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

$(BUILD)/%.o: $(SRC)/**/**/%.cpp $(SRC)/**/**/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

$(BUILD)/main.o: $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

rebuild: clean build

run: all
	./$(APP_NAME)

refresh: clean run

clean:
	rm -f $(APP_NAME) *.o $(BUILD)/*.o
