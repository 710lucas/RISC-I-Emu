
#include <iostream>
#include <fstream>
#include "./emulator/cpu.h"
#include "./emulator/memory/memory.hpp"
#include "./emulator/BUS/systemBus.hpp"
#include "./emulator/IO/disk/disk.hpp"
#include "./Emulator/IO/display/display.hpp"
#include "./emulator/IO/keyboard/keyboard.hpp"
#include <cstring>

typedef unsigned char byte;

int main(int argc, char* argv[]){


    if(argc == 1){
        std::cout<<"File path not found, use --help to see the commands\n";
        return 0;
    }

    else if(argc == 2){
        if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
            std::cout<<"Use --file <file_path> to specify the path\n";
        return 0;
    }

    else if(argc == 3 && strcmp(argv[1], "--file") == 0){

        SystemBus* bus = new SystemBus();

        Memory* mem =  new Memory(2048, *bus);
        bus->setMemoryModule(mem);

        Disk* disk = new Disk(*bus); 
        bus->setDiskModule(disk);

        Display* display = new Display(*bus);
        bus->setDisplayModule(display);

        Keyboard* keyboard = new Keyboard(*bus);
        bus->setKeyboardModule(keyboard);

        Cpu* cpu = new Cpu(*bus);


        char* filePath = argv[2];
        std::ifstream file(filePath, std::ios::binary);

        if(!file.is_open()){
            std::cerr<<"Error opening file\n";
            return 1;
        }

        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        char* buffer = new char[fileSize];

        file.read(buffer, fileSize);

        if(!file){
            std::cerr<<"Error reading file\n";
            file.close();
            return 1;
        }

        for(int i = 0; i<fileSize; i++){
            mem->write(i, static_cast<byte>(buffer[i]));
        }

        file.close();

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(64, 64, "RISC-I Emulator");

        int result = 0;

        ClearBackground(WHITE);
        while(!WindowShouldClose()){

            keyboard->keyboardLoop();

            if(result == 0){
                result = cpu->cycle();
            }

            display->displayLoop();

        }

        CloseWindow();

    }


}