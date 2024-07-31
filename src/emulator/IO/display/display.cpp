#include "display.hpp"

Display::Display(SystemBus &bus) : IOInterface(bus){
    this->displayBuffer = std::vector<std::vector<std::string>>(displaySize, std::vector<std::string>(displaySize, emptyChar));
}

void Display::write(byte data){
}

void Display::read(long address){
}

void Display::displayText(byte address, byte size){

    std::string text = "";
    for(int i = 0; i < size; i++){
        this->getBus()->writeAddress(address+i);
        this->getBus()->writeControl(MEMREAD);
        this->getBus()->execute();
        text += static_cast<char>(this->getBus()->readData());
    }

    this->displayBuffer[y][x] = text;
}

void Display::displayPixel(){
    this->displayBuffer[y][x] = "X";
}

void Display::clearDisplay(){
    this->displayBuffer = std::vector<std::vector<std::string>>(displaySize, std::vector<std::string>(displaySize, emptyChar));
}

void Display::clearPixel(){
    this->displayBuffer[y][x] = emptyChar;
}

void Display::setX(int x){
    this->x = x;
}

void Display::setY(int y){
    this->y = y;
}

byte Display::execute(byte control, byte address, byte data){
    switch(control){
        case SETCRDX:
            this->setX(static_cast<int>(data));
            break;
        case SETCRDY:
            this->setY(static_cast<int>(data));
            break;
        case PXDSPL:
            this->displayPixel();
            break;
        case TXTDSPL:
            this->displayText(address, data);
            break;
        case CLRDSPL:
            clearDisplay();
            break;
        case CLRPXL:
            clearPixel();
            break;
        case PRNTDSPL:
            printDisplay();
            break;
    }

    return 0;
}

void Display::printDisplay(){
    for(const auto& row: this->displayBuffer){
        for(const auto& col: row){
            std::cout << col;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}