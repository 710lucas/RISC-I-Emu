#include "memory.hpp"
#include <iostream>

Memory::Memory() : bus(*(new SystemBus())){
    this->memory = std::vector<byte>(256);
}

Memory::Memory(SystemBus &bus) : bus(bus){
    Memory();
}

Memory::Memory(long memory_size, SystemBus &bus) : bus(bus){
    this->memory = std::vector<byte>(memory_size);
}

byte Memory::read(long position){
    return position >= 0 && position < memory.size()  ?
        this->memory[position] : NULL;
}

void Memory::write(long position, byte data){
    if (position >= 0 && position < this->memory.size()) {
        this->memory[position] = data;
    } else {
    }
}

byte Memory::execute(byte control, byte address, byte data){
    if(control == MEMREAD){
        this->bus.writeData(this->read(address));
        this->bus.writeControl(END_MEMREAD);
    }
    else if(control == MEMWRITE){
        this->write(address, data);
    }
    return 0;
}


