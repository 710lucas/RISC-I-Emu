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

ModuleInterface* SystemBus::getMemoryModule(){
    return this->memoryModule;
}

ModuleInterface* SystemBus::getCpuModule(){
    return this->cpuModule;
}

void SystemBus::execute(){
    byte address = this->readAddress();
    byte data = this->readData();
    byte control = this->readControl();

    if(control >= MEMSTART && control <= MEMEND){
        // std::cout<<"Memory control signal: "<<control<<std::endl;
        // if(memoryModule == NULL)
        //     std::cerr<<"Memory module not set\n";   

        // std::cout<<"Memory module"<<memoryModule<<std::endl;
        // this->memoryModule->execute(control, address, data);
        if(memoryModule == NULL) {
            std::cerr << "Memory module not set\n";
            return; // Adiciona esta linha para retornar imediatamente
        }

        memoryModule->execute(control, address, data);
    }
    else{
        std::cout << "Invalid control signal : " << control << std::endl;
    }

}