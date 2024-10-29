
APP_NAME = hello_triangle

CXX = clang++
CXXFLAGS = -std=c++17
LDFLAGS = -lglfw

# Dependencies library
DEP = dep

# GLFW paths
GLFW_PAHT = $(DEP)/glfw
GLFW_INCLUDE_PATH = $(GLFW_PAHT)/include
GLFW_LIB_PATH = $(GLFW_PAHT)/lib

# GLAD paths
GLAD_PATH = $(DEP)/glad

INCLUDE = -I$(GLFW_INCLUDE_PATH) -I$(GLAD_PATH)
LIBS =  -L$(GLFW_LIB_PATH)

all: libs $(APP_NAME)

$(APP_NAME): main.o
	$(CXX) -o $(APP_NAME) main.o $(GLAD_PATH)/glad.o $(INCLUDE) $(LIBS) $(LDFLAGS)

libs:
	cd $(DEP)/glad && $(CXX) -o glad.o -Iinclude -c glad.c

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(INCLUDE)

run: all
	./$(APP_NAME)

clean:
	rm -f *.o $(APP_NAME)
