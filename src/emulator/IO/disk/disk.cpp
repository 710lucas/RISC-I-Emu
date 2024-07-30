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

    const long lineNumber = this->getBus()->readAddress();


    /*
        To be able to add a byte to any line we need to
        read the file so we can edit the line that we want
        and then rewrite the file with the new data

        We can't edit a specific line with std::ofstream
    */

    //Preparing to read file
    std::ifstream readingFile("disk.txt");
    std::vector<std::string> lines;
    std::string line;

    //Reading file
    if(readingFile.is_open()){
        while(std::getline(readingFile, line)){
            lines.push_back(line);
        }
        readingFile.close();
    }

    //Adding empty lines if the file is too short
    while(lines.size() <= lineNumber){
        lines.push_back("");
    }

    //Editing the line
    lines[lineNumber] = std::to_string(static_cast<int>(data));


    std::ofstream file("disk.txt");

    //Rewriting to file
    std::ofstream writingFile("disk.txt");

    if(writingFile.is_open()){
        for(const auto& line: lines){
            writingFile << line << "\n";
        }
        writingFile.close();
    } 

    else {
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