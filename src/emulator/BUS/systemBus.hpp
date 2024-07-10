#pragma once

#include "./bus_lane/bus.hpp"
#include "./bus_module/busModule.hpp"
#include <vector>

typedef short twoBytes;
typedef unsigned char byte;

// Info about the memory's instructions
// Each set of instructions is going to
//   have a range, memory's range is from
//   0x00 to 0x01
#define MEMSTART 0xF0 //Memory start
#define MEMEND 0xF1 //Memory end

// Info about the CPU's instructions
#define CPUSTART 0xF2 //CPU start
#define CPUEND 0xF3 //CPU end

#define MEMWRITE 0xF0 //Memory write to the bus
#define MEMREAD 0xF1 //Memory read from the bus
#define CPUREAD 0xF2 //Interruption to make CPU read the BUS
#define CPUWRITE 0xF3  //Interruption to make CPU write to the BUS

class SystemBus{

    private:
        Bus dataBus;
        Bus addressBus;
        Bus controlBus;

        ModuleInterface* memoryModule;
        ModuleInterface* cpuModule;

    public:
        SystemBus();
        void writeData(byte value);
        void writeAddress(byte value);
        void writeControl(byte value);
        byte readData();
        byte readAddress();
        byte readControl();

        void setMemoryModule(ModuleInterface* module);
        void setCpuModule(ModuleInterface* module);

        ModuleInterface* getMemoryModule();
        ModuleInterface* getCpuModule();

        void execute();

};