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
#define SETCRDX  0xF7 //Setting X coordinate to display
#define SETCRDY  0xF8 //Setting Y coordinate to display
#define PXDSPL   0xF9 //Displaying pixel
#define TXTDSPL  0xFA //Displaying text
#define CLRDSPL  0xFB //Clearing display
#define CLRPXL   0xFC //Clearing pixel   
#define SCREENSTART SETCRDX
#define SCREENEND CLRPXL


class SystemBus{

    private:
        Bus dataBus;
        Bus addressBus;
        Bus controlBus;

        ModuleInterface* memoryModule;
        ModuleInterface* cpuModule;
        ModuleInterface* diskModule;
        ModuleInterface* displayModule;

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
        void setDisplayModule(ModuleInterface* module);

        ModuleInterface* getMemoryModule();
        ModuleInterface* getCpuModule();
        ModuleInterface* getDiskModule();
        ModuleInterface* getScreenModule();

        void execute();

};