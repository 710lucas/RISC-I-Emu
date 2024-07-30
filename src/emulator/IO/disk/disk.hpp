#pragma once

#include "../IO.hpp"
#include "../../BUS/systemBus.hpp"

/*
    Disclaimer

    This implementation is just an example for a real DISK
    We will be storing data in a txt file and reading from it
    Each byte will be stored in a new line
*/


class Disk : public IOInterface{

    private:


    public :

        Disk(SystemBus &bus);


        //Write to DISK
        virtual void write(byte data) override;

        //Read from DISK
        virtual void read(long address) override;

        //Execute IO operation  
        virtual byte execute(byte control, byte address, byte data) override;


};