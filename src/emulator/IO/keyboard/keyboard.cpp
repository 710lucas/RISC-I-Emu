#include "./keyboard.hpp"
#include <raylib.h>
#include <iostream>

Keyboard::Keyboard(SystemBus &bus) : IOInterface(bus){

}

void Keyboard::write(byte data){
    //Write to keyboard
    //Does nothing
}

void Keyboard::read(long address){
    //Read from keyboard
    //Does nothing
}

byte Keyboard::execute(byte control, byte address, byte data){
    //Execute IO operation

    SystemBus* bus = this->getBus();

    if(control == KEYREAD){

        bus->writeData(this->pressedKey);
        bus->writeAddress(address);
        bus->writeControl(MEMWRITE);
        bus->execute();
        if(this->pressedKey != 0){
            // std::cout<<"Memory write: "<<this->pressedKey<<std::endl;
        }
    }

    if(control == KEYWRITE){
        this->pressedKey = data;
    }

    return 0;
}

void Keyboard::keyboardLoop(){
    int pressedKey = GetKeyPressed();
    this->pressedKey = pressedKey;
}