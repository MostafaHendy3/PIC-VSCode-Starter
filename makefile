# XC8 compiler and options
CC = xc8-cc
CFLAGS = -mcpu=16F877A -O0 -std=C99

# Project name
TARGET = application

# Source files
SRCS = $(wildcard *.c) $(wildcard */*.c)

# Object files directory
OBJDIR = build

# Object files
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.p1))

# Default target
all: $(TARGET).hex

# Rule to compile C files
$(OBJDIR)/%.p1: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate hex file
$(TARGET).hex: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET).hex

# Clean
clean:
	rm -f $(OBJS) $(TARGET).hex

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(dir $(OBJS)))
.PHONY: clean