#include "./IO.hpp"

IOInterface::IOInterface(SystemBus &bus) : bus(bus){

}   

SystemBus* IOInterface::getBus(){
    return &this->bus;
}