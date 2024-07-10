#pragma once

#include "./bus_lane/bus.hpp"
#include "./bus_module/busModule.hpp"
#include <vector>

typedef short twoBytes;
typedef unsigned char byte;

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