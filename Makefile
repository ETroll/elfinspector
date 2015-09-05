# Simple makefile

TARGET = elfinspector

COMPILER = clang
LINKER = clang

COMPILE_FLAGS = -Wall -std=c99
LINK_FLAGS = -lncurses

OBJECT_DIR = obj/
SOURCE_DIR = src/
BUILD_DIR = bin/


# ---- Build stuff below ----------------

OBJECTS := $(patsubst $(SOURCE_DIR)%.c,$(OBJECT_DIR)%.o,$(wildcard $(SOURCE_DIR)*.c))

all: clean $(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(OBJECT_DIR)

$(OBJECTS): $(OBJECT_DIR)
	$(COMPILER) $(COMPILE_FLAGS) -c $(patsubst $(OBJECT_DIR)%.o, $(SOURCE_DIR)%.c, $@) -o $@

$(TARGET): $(OBJECTS) $(BUILD_DIR)
	$(LINKER) $(LINK_FLAGS) $(OBJECTS) -o $(BUILD_DIR)$(TARGET)

$(OBJECT_DIR):
	mkdir $@

$(BUILD_DIR):
	mkdir $@
