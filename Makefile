# all:
# 	g++ ./src/main.cpp ./src/emulator/emulator.cpp -o Emulator

SRCS := $(shell find src -name '*.cpp')
CFLAGS := $(foreach src,$(SRCS),-c $(src))
# Define o alvo padrão
all:
	g++ $(SRCS) -g -o Emulator -lraylib -lgdi32 -lwinmm

clean: 
	rm Emulator