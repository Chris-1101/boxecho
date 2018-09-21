# Directory Structure
DIR_SRC = src
DIR_INC = include
DIR_OBJ = obj
DIR_BIN = bin

# Source Files and Dependencies
SOURCES = $(wildcard $(DIR_SRC)/*.c)
HEADERS = $(wildcard $(DIR_INC)/*.h)
OBJECTS = $(SOURCES:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

# Compiler Options
CC      = gcc
CFLAGS  = -Wall -iquote $(DIR_INC)/ #-g
TARGET  = boxecho

# Make Options
.PHONY: default all clean
default: all

# main.o
$(DIR_OBJ)/main.o: $(DIR_SRC)/main.c $(HEADERS)
	$(CC) -c $(DIR_SRC)/main.c -o $(DIR_OBJ)/main.o $(CFLAGS)

# checkalloc.o
$(DIR_OBJ)/checkalloc.o: $(DIR_SRC)/checkalloc.c $(DIR_INC)/checkalloc.h
	$(CC) -c $(DIR_SRC)/checkalloc.c -o $(DIR_OBJ)/checkalloc.o $(CFLAGS)

# getinput.o
$(DIR_OBJ)/getinput.o: $(DIR_SRC)/getinput.c $(DIR_INC)/getinput.h $(DIR_INC)/checkalloc.h
	$(CC) -c $(DIR_SRC)/getinput.c -o $(DIR_OBJ)/getinput.o $(CFLAGS)

# printc.o
$(DIR_OBJ)/printc.o: $(DIR_SRC)/printc.c $(DIR_INC)/printc.h $(DIR_INC)/checkalloc.h
	$(CC) -c $(DIR_SRC)/printc.c -o $(DIR_OBJ)/printc.o $(CFLAGS)

# termwidth.o
$(DIR_OBJ)/termwidth.o: $(DIR_SRC)/termwidth.c $(DIR_INC)/termwidth.h
	$(CC) -c $(DIR_SRC)/termwidth.c -o $(DIR_OBJ)/termwidth.o $(CFLAGS)

# strtrm.o
$(DIR_OBJ)/strtrm.o: $(DIR_SRC)/strtrm.c $(DIR_INC)/strtrm.h
	$(CC) -c $(DIR_SRC)/strtrm.c -o $(DIR_OBJ)/strtrm.o $(CFLAGS)

# Main Command
all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(DIR_BIN)/$(TARGET) $(CFLAGS)

# Clean Up Command
clean:
	rm -r $(DIR_OBJ)/*
