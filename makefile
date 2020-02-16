
TARGET = iso-tanks
SRC_DIR = src
OBJ_DIR = obj

CPP_FILES  = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
H_FILES   = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/**/*.h)
OBJ_FILES = $(wildcard $(OBJ_DIR)/*.o) $(wildcard $(OBJ_DIR)/**/*.o)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
OBJS := $(subst /src/,/,$(OBJS))

CXX = gcc
CXXFLAGS = -lsfml-system -lsfml-window -lGLEW -lGL -lstdc++
INCLUDES = -Ilib/qu3e/src

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $?

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(CPP_FILES)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

