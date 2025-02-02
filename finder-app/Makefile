#make CROSS_COMPILE=aarch64-none-linux-gnu-

ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE :=
endif

# Compiler and linker commands
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

# Source files
SRCS = writer.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = writer

# Compiler flags
#CFLAGS = -Wall -Wextra -O2

# Linker flags
LDFLAGS =

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)