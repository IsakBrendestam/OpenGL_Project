
APP_NAME := hello_triangle

CXX := clang++
CXXFLAGS := -std=c++17
LDFLAGS := -lglfw

# Directories
BUILD := build
DEP := dep
SRC := src

# GLFW paths
GLFW_PAHT := $(DEP)/glfw
GLFW_INCLUDE_PATH := $(GLFW_PAHT)/include
GLFW_LIB_PATH := $(GLFW_PAHT)/lib

# GLAD paths
GLAD_PATH := $(DEP)/glad

INCLUDE := -I$(GLFW_INCLUDE_PATH) -I$(GLAD_PATH)
LIBS :=  -L$(GLFW_LIB_PATH)

SRC_FILES := $(shell find $(SRC) -name '*.cpp')
FILES := $(patsubst %.cpp, $(BUILD)/%.o, $(notdir $(SRC_FILES)))

all: libs $(APP_NAME)

$(APP_NAME): main.o $(FILES)
	echo $^
	$(CXX) -o $(APP_NAME) main.o $(GLAD_PATH)/glad.o $(INCLUDE) $(LIBS) $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

$(BUILD)/%.o: $(SRC)/**/%.cpp $(SRC)/**/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

libs:
	cd $(DEP)/glad && $(CXX) -o glad.o -Iinclude -c glad.c && ar -rc glad.a glad.o

main.o: main.cpp EngineSettings.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(INCLUDE)

run: all
	./$(APP_NAME)

clean:
	rm -f $(APP_NAME) *.o $(BUILD)/*.o
