
TARGET = iso-tanks
SRC_DIR = src
OBJ_DIR = obj
ASSET_DIR = assets

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CPP_FILES   = $(call rwildcard,$(SRC_DIR)/,*.cpp)
H_FILES     = $(call rwildcard,$(SRC_DIR)/,*.h)
OBJ_FILES   = $(call rwildcard,$(OBJ_DIR)/,*.o)
BLEND_FILES = $(call rwildcard,$(ASSET_DIR)/,*.blend)

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(CPP_FILES))
OBJS := $(subst /$(SRC_DIR)/,/,$(OBJS))
ASSETS = $(patsubst %.blend,%.obj,$(BLEND_FILES))

BLENDER = blender

CXX = gcc
CXXFLAGS = -lsfml-system -lsfml-window -lm -lGLEW -lGL -lstdc++ -lLinearMath -lBulletDynamics -lBulletCollision -lBulletSoftBody
INCLUDES = -I/usr/include/bullet/
LIBS =

$(TARGET): $(OBJS) $(ASSETS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

$(ASSET_DIR)/%.obj: $(ASSET_DIR)/%.blend $(BLEND_FILES)
	$(BLENDER) $< -b -P $(SRC_DIR)/util/blender_export.py

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(CPP_FILES)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

