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
#define MEMEND 0xF2 //Memory end

// Info about the CPU's instructions
#define CPUSTART 0xF3 //CPU start
#define CPUEND 0xF4 //CPU end

#define MEMWRITE MEMSTART //Bus requesting to write to memory; Bus write to memory
#define MEMREAD 0xF1 //Bus requesting to read from memory; Bus read from memory
#define END_MEMREAD MEMEND
#define CPUREAD 0xF3 //Bus interrupting CPU to read from the BUS; Cpu read from the BUS
#define CPUWRITE 0xF4  //Bus interrupting CPU to write to the BUS; Bus write to CPU


// Info about the IO's DISK instructions

#define DISKREAD 0xF5 //Bus requesting to read from DISK; Bus read from DISK
#define DISKWRITE 0xF6 //Bus requesting to write to DISK; Bus write to DISK

#define DISKSTART DISKREAD
#define DISKEND DISKWRITE

// Info about the IO's SCREEN instructions
#define SCREENSTART SCREENWRITE
#define SCREENEND SCREENWRITE

#define SCREENWRITE 0xF7 //Bus requesting to write to SCREEN; Bus write to SCREEN


class SystemBus{

    private:
        Bus dataBus;
        Bus addressBus;
        Bus controlBus;

        ModuleInterface* memoryModule;
        ModuleInterface* cpuModule;
        ModuleInterface* diskModule;
        ModuleInterface* screenModule;

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
        void setDiskModule(ModuleInterface* module);
        void setScreenModule(ModuleInterface* module);

        ModuleInterface* getMemoryModule();
        ModuleInterface* getCpuModule();
        ModuleInterface* getDiskModule();
        ModuleInterface* getScreenModule();

        void execute();

};