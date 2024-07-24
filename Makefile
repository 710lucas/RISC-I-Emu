# all:
# 	g++ ./src/main.cpp ./src/emulator/emulator.cpp -o Emulator

SRCS := $(shell find src -name '*.cpp')

# Define o alvo padrão
all:
	g++ $(SRCS) -g -o Emulator
