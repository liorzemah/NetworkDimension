CC := /usr/bin/g++
CFLAGS := -Wall -g

ifeq (,$(TEST_NAME)) 
	TEST_NAME := PacketCaptureEngine
endif
TARGET := exec/$(TEST_NAME).out

OBJ_DIR := obj

SRCS := $(wildcard src/Types/IpAddressTypes/*.cpp src/Types/*.cpp src/*.cpp tests/$(TEST_NAME).cpp)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC)  $(CFLAGS) -o $@ $(SRCS) -std=c++14 -lpcap -lpthread -lstdc++fs -I/home/lior/VSCODE_PROJ/NetworkDimension/src

clean:
	rm $(TARGET)