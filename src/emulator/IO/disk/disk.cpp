#include "./disk.hpp"
#include <iostream>
#include <fstream>
#include <vector>

/*
    Disclaimer

    This implementation is just an example for a real DISK
    We will be storing data in a txt file and reading from it
    Each byte will be stored in a new line
*/


Disk::Disk(SystemBus &bus) : IOInterface(bus){
}   

void Disk::write(byte data){

    const long bytePosition = this->getBus()->readAddress();


    /*
        To be able to add a byte to any line we need to
        read the file so we can edit the line that we want
        and then rewrite the file with the new data

        We can't edit a specific line with std::ofstream
    */

    //Making sure the file exists
    std::ofstream file("disk.bin", std::ios::binary | std::ios::app);
    file.close();

    //Opening file for writing
    std::ofstream writingFile("disk.bin", std::ios::binary | std::ios::in | std::ios::out);

    if(!writingFile.is_open()){
         std::cout << "Unable to open file\n";
         return;
    }

    //move the file pointer to the desired line
    writingFile.seekp(bytePosition, std::ios::beg);

    //write the byte
    writingFile.write(reinterpret_cast<const char *>(&data), sizeof(byte));
    writingFile.close();

}

void Disk::read(int memAddress, long diskAddress){

    byte readData;

    std::ifstream file("disk.bin", std::ios::binary);

    if(!file.is_open()){
        std::cout << "Unable to open file\n";
        return;
    }

    //move the file pointer to the desired line
    file.seekg(diskAddress, std::ios::beg);

    //read the byte
    file.read(reinterpret_cast<char *>(&readData), sizeof(byte));

    //Sending data to the memory address requested by data
    this->getBus()->writeData(readData);
    this->getBus()->writeControl(MEMWRITE);
    this->getBus()->writeAddress(memAddress);
    this->getBus()->execute();


    file.close();

}


byte Disk::execute(byte control, byte address, byte data){
    if(control == DISKREAD){
        this->read(data, address);
        this->getBus()->writeControl(DISKEND);
    }
    else if(control == DISKWRITE){
        this->write(data);
        this->getBus()->writeControl(DISKEND);
    }
    return 0;
}