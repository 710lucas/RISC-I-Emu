#pragma once

#include <stdio.h>
#include <cstdint>
#include <iostream>

typedef short twoBytes;
typedef unsigned char byte;

class Emulator
{
private:

    long memory_size = 4096;

    byte operandCap = 0x20;

    int registers[32] = {0};
    bool carry = false;

    long pc = 0;

    byte* memory;

    const int maxValue = (1 << (sizeof(int) * 8 - 1)) - 1;
    const int minValue = -(1 << (sizeof(short) * 8 - 1));


public:
    Emulator(/* args */);
    Emulator(long memory_size);

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
    void executeInstruction(byte instruction);
    void cycle();
};

