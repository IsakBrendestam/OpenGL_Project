
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

# GLM paths
GLM_PATH := $(DEP)/glm

# ImGui paths
IMGUI_PATH := $(DEP)/imgui
IMGUI_BACKEND_PATH := $(DEP)/imgui/backends

# Libraries
INCLUDE := -I$(DEP) -I$(GLFW_INCLUDE_PATH) -I$(GLAD_PATH) -I$(GLM_PATH) -I$(IMGUI_PATH) -I$(IMGUI_BACKEND_PATH) -I$(SRC)
LIBS :=  -L$(GLFW_LIB_PATH)

SRC_FILES := $(shell find $(SRC) -name '*.cpp')
FILES := $(patsubst %.cpp, $(BUILD)/%.o, $(notdir $(SRC_FILES))) $(BUILD)/main.o

all: build

IMGUI_FILES := $(IMGUI_PATH)/imgui.o $(IMGUI_PATH)/imgui_draw.o $(IMGUI_PATH)/imgui_tables.o $(IMGUI_PATH)/imgui_widgets.o 
IMGUI_FILES += $(IMGUI_BACKEND_PATH)/imgui_impl_glfw.o $(IMGUI_BACKEND_PATH)/imgui_impl_opengl3.o
libs: $(IMGUI_FILES)
	cd $(GLAD_PATH) && $(CXX) -o glad.o -Iinclude -c glad.c    # && ar -rc glad.a glad.o

$(IMGUI_PATH)/%.o: $(IMGUI_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

$(IMGUI_BACKEND_PATH)/%.o: $(IMGUI_BACKEND_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE)

build: $(libs) $(APP_NAME)

$(APP_NAME): $(FILES)
	$(CXX) $(LDFLAGS) -o $@ $^ $(IMGUI_FILES) $(GLAD_PATH)/glad.o $(INCLUDE) $(LIBS)

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
