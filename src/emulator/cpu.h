#pragma once

#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "./BUS/bus_module/busModule.hpp"
#include "./stack/stack.h"
#include "./BUS/systemBus.hpp"

typedef short twoBytes;
typedef unsigned char byte;

class Cpu{
private:

    byte operandCap = 0x20;

    int registers[32] = {0};
    bool carry = false;

    long pc = 0;

    const int maxValue = (1 << (sizeof(int) * 8 - 1)) - 1;
    const int minValue = -(1 << (sizeof(short) * 8 - 1));

    Stack stack = Stack();

    SystemBus& bus;


public:
    Cpu(/* args */);
    Cpu(SystemBus &bus);

    byte getRegister(long position);
    void setRegister(long position, byte value);

    byte* getRegisters();

    byte getOperandCap();
    void setOperandCap(byte operandCap);

    bool getCarry();
    void setCarry(bool carry);

    long getPc();
    void setPc(long pc);

    byte getMemory(long position);
    void setMemory(long position, byte data);

    void loadIntoMemory(byte toLoad[]);
    byte getOperandValue(byte lower, byte higher);
    int executeInstruction(byte instruction);
    void cycle();
};

