#include "systemBus.hpp"
#include <iostream>


SystemBus::SystemBus(){
    this->dataBus = Bus();
    this->addressBus = Bus();
    this->controlBus = Bus();
}

void SystemBus::writeData(byte value){
    this->dataBus.write(value);
}

void SystemBus::writeAddress(byte value){
    this->addressBus.write(value);
}

void SystemBus::writeControl(byte value){
    this->controlBus.write(value);
}

byte SystemBus::readData(){
    return this->dataBus.read();
}

byte SystemBus::readAddress(){
    return this->addressBus.read();
}

byte SystemBus::readControl(){
    return this->controlBus.read();
}

void SystemBus::setMemoryModule(ModuleInterface* module){
    this->memoryModule = module;
}

void SystemBus::setCpuModule(ModuleInterface* module){
    this->cpuModule = module;
}

void SystemBus::setDiskModule(ModuleInterface* module){
    this->diskModule = module;
}

void SystemBus::setDisplayModule(ModuleInterface* module){
    this->displayModule = module;
}

void SystemBus::setKeyboardModule(ModuleInterface* module){
    this->keyboardModule = module;
}

ModuleInterface* SystemBus::getMemoryModule(){
    return this->memoryModule;
}

ModuleInterface* SystemBus::getCpuModule(){
    return this->cpuModule;
}

ModuleInterface* SystemBus::getDiskModule(){
    return this->diskModule;
}

ModuleInterface* SystemBus::getScreenModule(){
    return this->displayModule;
}

ModuleInterface* SystemBus::getKeyboardModule(){
    return this->keyboardModule;
}

void SystemBus::execute(){
    byte address = this->readAddress();
    byte data = this->readData();
    byte control = this->readControl();

    if(control >= MEMSTART && control <= MEMEND){
        if(memoryModule == NULL) {
            std::cerr << "Memory module not set\n";
            return;
        }

        memoryModule->execute(control, address, data);
    }
    else if((control >= DISKSTART) && (control <= DISKEND)){
        if(diskModule == NULL) {
            std::cerr << "Disk module not set\n";
            return;
        }

        diskModule->execute(control, address, data);
    }

    else if((control >= SCREENSTART) && (control <= SCREENEND)){
        if(displayModule == NULL) {
            std::cerr << "Display module not set\n";
            return;
        }

        displayModule->execute(control, address, data);
    }

    else if((control >= KEYSTART) && (control <= KEYEND)){
        if(keyboardModule == NULL) {
            std::cerr << "Keyboard module not set\n";
            return;
        }

        keyboardModule->execute(control, address, data);
    }
    
    else{
        std::cout << "Invalid control signal : " << static_cast<int>(control) << std::endl;
    }

}