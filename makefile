
TARGET = iso-tanks
SRC_DIR = src
OBJ_DIR = obj

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CPP_FILES = $(call rwildcard,$(SRC_DIR)/,*.cpp)
H_FILES   = $(call rwildcard,$(SRC_DIR)/,*.h)
OBJ_FILES = $(call rwildcard,$(OBJ_DIR)/,*.o)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
OBJS := $(subst /src/,/,$(OBJS))

CXX = gcc
CXXFLAGS = -lsfml-system -lsfml-window -lm -lGLEW -lGL -lstdc++
INCLUDES = -Ilib/qu3e/src

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $?

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(CPP_FILES)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

