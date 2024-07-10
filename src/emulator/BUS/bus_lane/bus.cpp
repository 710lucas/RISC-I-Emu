#include "bus.hpp"
#include <iostream>

Bus::Bus(){
    this->value = 0x00;
}

byte Bus::read(){
    return this->value;
}

void Bus::write(byte value){
    this->value = value;
}