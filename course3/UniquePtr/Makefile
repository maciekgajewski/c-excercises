# Makefile for MyUniquePtr and test
#CC = g++
CC = clang++

# compiler flags:
CFLAGS  = -g -Wall --std=c++14 --stdlib=libc++ 

# the build target executable:
TARGET = class_test

all: $(TARGET)

$(TARGET): ptr_test.cc
	$(CC) $(CFLAGS) -o $(TARGET) ptr_test.cc

clean:
	$(RM) -rf $(TARGET) $(TARGET).dSYM
