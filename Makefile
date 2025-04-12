CXX       := c++
CC        := cc

CXXFLAGS  := -Wall
CFLAGS    := -Wall
LDFLAGS   := -L/usr/lib -lstdc++ -lm

GLFW_DIR  := ./glfw/build/src
GLFWFLAGS := -L$(GLFW_DIR) -lglfw3 -lX11 -lXrandr -lXi -lXxf86vm -lXcursor -ldl -lpthread -lGL

BUILD     := build
OBJ_DIR   := $(BUILD)/objects
OUT_DIR   := out
TARGET    := main

INCLUDE   := -Iinclude/
EXT       := cpp

SRCCPP    := $(filter-out src/glad.c, $(wildcard src/*.$(EXT)))
GLAD_SRC  := src/glad.c
SRC       := $(SRCCPP) $(GLAD_SRC)

OBJECTS   := $(SRCCPP:src/%.cpp=$(OBJ_DIR)/%.o) \
             $(GLAD_SRC:src/%.c=$(OBJ_DIR)/%.o)

DEPENDENCIES := $(OBJECTS:.o=.d)

all: build $(OUT_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(OUT_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(GLFWFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info run

build:
	@mkdir -p $(BUILD)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: CFLAGS += -DDEBUG -g
debug: all

run: all
	@./$(OUT_DIR)/$(TARGET)

clean:
	-@rm -rvf $(BUILD)
	-@rm -rvf $(OUT_DIR)

info:
	@echo "[*] Output dir:      ${OUT_DIR}"
	@echo "[*] Object dir:      ${OBJ_DIR}"
	@echo "[*] Source files:    ${SRC}"
	@echo "[*] Objects:         ${OBJECTS}"
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
