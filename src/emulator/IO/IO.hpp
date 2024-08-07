#pragma once

#include "../BUS/bus_module/busModule.hpp"
#include "../BUS/systemBus.hpp"

#define DISKREAD 0xF5 //Disk requesting read from memory;
#define DISKWRITE 0xF6
#define DISKEND DISKWRITE
#define DISKSTART DISKREAD

class IOInterface : public ModuleInterface{

    private: 
        SystemBus& bus;

    public:

        IOInterface(SystemBus &bus);

        SystemBus* getBus();


        // Write data to bus
        virtual void write(byte data) = 0;

        // Read data from bus
        virtual void read(int data, long address) = 0;

        // Execute IO operation
        virtual byte execute(byte control, byte address, byte data) = 0;


};