#include "systemBus.hpp"
#include <iostream>

// Info about the memory's instructions
// Each set of instructions is going to
//   have a range, memory's range is from
//   0x00 to 0x01
#define MEMSTART 0x00 //Memory start
#define MEMEND 0x01 //Memory end

// Info about the CPU's instructions
#define CPUSTART 0x02 //CPU start
#define CPUEND 0x03 //CPU end

#define MEMWRITE 0x00 //Memory write to the bus
#define MEMREAD 0x01 //Memory read from the bus
#define CPUREAD 0x02 //Interruption to make CPU read the BUS
#define CPUWRITE 0x03  //Interruption to make CPU write to the BUS

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
        this->memoryModule->execute(control, address, data);
    }
    else if(control >= CPUSTART && control <= CPUEND){
        this->cpuModule->execute(control, address, data);
    }
    else{
        std::cout << "Invalid control signal : " << control << std::endl;
    }

}