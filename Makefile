# Detecting OS

ifeq ($(OS), Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname)
endif


SRCS := $(shell find src -name '*.cpp')
CFLAGS := -Wall -Wextra

ifeq ($(DETECTED_OS), Windows)
    LDFLAGS := -lraylib -lgdi32 -lwinmm
    RM := rm .\Emulator.exe

else ifeq ($(DETECTED_OS), Linux)
    LDFLAGS := -lraylib
    RM := rm Emulator
endif

# Define o alvo padrão
all:
	g++ $(SRCS) $(CFLAGS) -g -o Emulator $(LDFLAGS) 

clean: 
	$(RM) 
