#include "./disk.hpp"
#include <iostream>
#include <fstream>

/*
    Disclaimer

    This implementation is just an example for a real DISK
    We will be storing data in a txt file and reading from it
    Each byte will be stored in a new line
*/


Disk::Disk(SystemBus &bus) : IOInterface(bus){
}   

void Disk::write(byte data){

    std::ofstream file("disk.txt");

    if(file.is_open()){
        file << static_cast<int>(data) << '\n';
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }

}

void Disk::read(long address){

    std::ifstream file("disk.txt");

    if(file.is_open()){
        std::string line;
        int currentLine = 0;
        while(std::getline(file, line)){
            if(currentLine == address){
                this->getBus()->writeData(static_cast<byte>(std::stoi(line)));
                break;
            }
            currentLine++;
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }

}


byte Disk::execute(byte control, byte address, byte data){
    if(control == DISKREAD){
        this->read(address);
        this->getBus()->writeControl(DISKEND);
    }
    else if(control == DISKWRITE){
        this->write(data);
        this->getBus()->writeControl(DISKEND);
    }
    return 0;
}