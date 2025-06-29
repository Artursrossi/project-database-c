# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./src
DEPFLAGS = -MMD -MP

# Directories
SRC_DIR := src
BUILD_DIR := build
TARGET := database

# Find all source and object files
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

# Default rule
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

# Compile source files to object files
# This rule ensures directory exists and compiles .c to .o
  # Create the necessary directory structure inside build/ if it doesn't exist
  # Compile the .c file into a .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean

# Include dependency files if they exist
-include $(DEPS)