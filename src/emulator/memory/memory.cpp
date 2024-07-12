#include "memory.hpp"

Memory::Memory(){
    this->memory = std::vector<byte>(256);
}

Memory::Memory(SystemBus bus){
    this->bus = bus;
    Memory();
}

Memory::Memory(long memory_size, SystemBus bus){
    this->memory = std::vector<byte>(memory_size);
    this->bus = bus;
}

byte Memory::read(long position){
    return position >= 0 && position < memory.size()  ?
        this->memory[position] : NULL;
}

void Memory::write(long position, byte data){
    this->memory[position] = data;
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


