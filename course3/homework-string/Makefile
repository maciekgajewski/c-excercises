# Makefile for MyUniquePtr and test
#CC = g++
CC = clang++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall --std=c++14 --stdlib=libc++
INCLUDES = -I../UniquePtr


# the build target executable:
TARGET = MyString

all: $(TARGET)

$(TARGET): my_string.cc
	$(CC) $(CFLAGS) $(INCLUDES)  -o $(TARGET) my_string.cc test.cc

clean:
	$(RM) -rf $(TARGET) 
	$(RM) -r $(TARGET).dSYM
