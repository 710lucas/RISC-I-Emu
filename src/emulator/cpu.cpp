#include "cpu.h"
#include <iostream>

#define ADD   0x01
#define ADDC  0x02
#define SUB   0x03
#define SUBC  0x04

#define AND   0x06
#define OR    0x07
#define XOR   0x08
#define SLL   0x09 //Shift left logical
#define SRL   0x0A //Shift right logical
#define SRA   0x0B //Shift right arithmetic
#define LDL   0x0C

#define STL   0x10

#define JMP    0x13
#define JMPR   0x14
#define CALL   0x15
#define CALLR  0x16

#define RET   0x17

#define RBUS  0x20 //Read from bus; data: firstVal; address: secondVal; control: thirdOp
#define WBUS  0x21 //Write to bus; data: firstVal; address: secondVal; control: thirdOp

/*
* Print
* This is just used for debug
* It prints the value stored on the register
*   referenced by the thirdOp
*
* Example: std::cout<<registers[thirdOp]<<"\n";
* 
*/
#define PRNT  0x18

#define STP   0x30

typedef unsigned char byte;

int byteToInt(byte byteVar);

Cpu::Cpu() : bus(*(new SystemBus())){
    this->stack = Stack();
}

Cpu::Cpu(SystemBus &bus) : bus (bus){
    Cpu();
}

int Cpu::cycle(){

    // Maybe put this in main


        this->bus.writeControl(MEMREAD);
        this->bus.writeAddress(pc);
        this->bus.execute();

        byte instruction = this->bus.readData();


        if(instruction == 0){
            std::cerr<<"Invalid instruction\n" << "PC: "<< pc << "\n";
            return -1;
        }

        int result = executeInstruction(instruction);

        if(result == 1){
            return 1;
        }

        this->bus.execute();

        // Run IO cycle

        pc+=6;

        return 0;

}

int Cpu::executeInstruction(byte instruction){


    byte firstOpLower, firstOpHigher;
    twoBytes firstOp;
    byte secondOpLower, secondOpHigher;
    twoBytes secondOp;
    byte thirdOp;

    this->bus.writeControl(MEMREAD);
    this->bus.writeAddress(pc+1);
    this->bus.execute();
    firstOpLower = this->bus.readData() & 0xFF;

    this->bus.writeAddress(pc+2);
    this->bus.writeControl(MEMREAD);
    this->bus.execute();
    firstOpHigher = this->bus.readData() & 0xFF;

    firstOp = ((firstOpLower) << 8) | firstOpHigher;

    this->bus.writeAddress(pc+3);
    this->bus.writeControl(MEMREAD);
    this->bus.execute();
    secondOpLower = this->bus.readData() & 0xFF;

    this->bus.writeAddress(pc+4);
    this->bus.writeControl(MEMREAD);
    this->bus.execute();
    secondOpHigher = this->bus.readData() & 0xFF;

    secondOp = ((secondOpLower) << 8) | secondOpHigher;

    this->bus.writeControl(MEMREAD);
    this->bus.writeAddress(pc+5);
    this->bus.execute();
    thirdOp = this->bus.readData() & 0xFF;

    byte firstVal = getOperandValue(firstOpLower, firstOpHigher);
    byte secondVal = getOperandValue(secondOpLower, secondOpHigher);

    int correctValue;
    long memory_location;

    switch (instruction)
    {
        case ADD:
        case ADDC:
            // std::cout<<"\n";
            // std::cout<<"ADD: \n";
            // std::cout<<"First value: "<<static_cast<int>(firstVal)<<"\n";
            // std::cout<<"Second value: "<<static_cast<int>(secondVal)<<"\n";
            correctValue = byteToInt(firstVal)+byteToInt(secondVal);

            if(instruction == ADDC && correctValue > maxValue){
                carry = true;
                correctValue &= maxValue;
            }

            registers[thirdOp] = correctValue;
            break;

        case SUB:
        case SUBC:
            correctValue = byteToInt(firstVal)-byteToInt(secondVal);

            if(instruction == SUBC && correctValue < minValue){
                carry = true;
                correctValue &= minValue;
            }

            registers[thirdOp] = correctValue;
            break;

        case AND:
            registers[thirdOp] = firstVal&secondVal;
            break;

        case OR:
            registers[thirdOp] = firstVal|secondVal;
            break;

        case XOR:
            registers[thirdOp] = firstVal^secondVal;
            break;

        case SLL:
            registers[thirdOp] = firstVal << secondVal;
            break;

        case SRL:
            registers[thirdOp] = firstVal >> secondVal;
            break;

        case SRA:
            registers[thirdOp] = byteToInt(firstVal) >> byteToInt(secondVal);
            break;

        case LDL:
        case STL:
            memory_location = byteToInt(firstVal)+byteToInt(secondVal);
            // std::cout<<"Memory location: "<<static_cast<int>(memory_location)<<"\n";
            if(instruction == LDL){
                this->bus.writeControl(MEMREAD);
                this->bus.writeAddress(memory_location);
                this->bus.execute();

                byte loadedValue = this->bus.readData();
                // std::cout<<"Loaded value: "<<static_cast<int>(loadedValue)<<"\n";
                // std::cout<<"register: "<<thirdOp<<"\n";

                registers[thirdOp] = loadedValue;

                // std::cout<<"Register value: "<<registers[thirdOp]<<"\n";
            }
            else if(instruction == STL){
                this->bus.writeControl(MEMWRITE);
                this->bus.writeAddress(memory_location);
                this->bus.writeData(registers[thirdOp]);
                this->bus.execute();
            }
            break;

        case JMP:
        case JMPR:
            if(registers[thirdOp] == 1){
                long jumpValue = byteToInt(firstVal)+byteToInt(secondVal);
                if(instruction == JMP)
                    pc = jumpValue;
                else
                    pc += jumpValue;
                pc -= 6; //considering that +=6 will be added after each instruction
            }
            break;

        case CALL:
        case CALLR:
            registers[thirdOp] = pc;
            if(instruction == CALL)
                pc = firstVal+secondVal;
            else
                pc += firstVal+secondVal;
            pc-=6;
            break;

        case RET:
            pc = firstVal+secondVal;
            pc -= 6;
            break;

        case PRNT:
            std::cout<<registers[thirdOp]<<"\n";
            break;

        case RBUS:
            registers[firstVal] = byteToInt(bus.readData());
            registers[secondVal] = byteToInt(bus.readAddress());
            registers[thirdOp] = byteToInt(bus.readControl());
            break;

        case WBUS:
            bus.writeData(firstVal);
            bus.writeAddress(secondVal);
            bus.writeControl(registers[thirdOp]);
            break;

        case STP:
            return 1;
        
        default:
            break;
    }

    return 0;

}


byte Cpu::getOperandValue(byte lower, byte higher){
    // std::cout<<"\ngetOperandValue\n";
    // std::cout<<"Lower: "<<static_cast<int>(lower)<<"\n";
    // std::cout<<"Higher: "<<static_cast<int>(higher)<<"\n";
    if(lower >= operandCap)
        return higher;
    // std::cout<<"Retrieving value from register: "<<static_cast<int>(lower)<<"\n";
    // std::cout<<"Value: "<<static_cast<int>(registers[lower])<<"\n\n";
    return registers[lower];

}

//Converts to an unsigned int
//There will be no negative numbers
int byteToInt(byte byteVar){
    return static_cast<unsigned int>(byteVar);
}
