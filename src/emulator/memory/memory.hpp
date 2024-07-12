#pragma once

#include "../BUS/bus_module/busModule.hpp"
#include "../BUS/systemBus.hpp"
#include <vector>   

class Memory : public ModuleInterface{

    private:
        SystemBus bus;
        std::vector<byte> memory;

    public:
        Memory();
        Memory(SystemBus bus);
        Memory(long memory_size, SystemBus bus);


        byte read(long position);
        void write(long position, byte data);

        virtual byte execute(byte control, byte address, byte data);
        

};