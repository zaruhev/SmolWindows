CC = gcc
CFLAGS = -Wall
LIBS = -lopengl32 -lgdi32 -lglu32

SOURCES = $(wildcard *.c)
 
OBJ_DIR = cache
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Target executable
TARGET = smoline.exe

# Default target
all: $(TARGET)

# Rule to create the object files directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to build object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY=clean
# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY=run
run: $(TARGET)
	./$(TARGET)
