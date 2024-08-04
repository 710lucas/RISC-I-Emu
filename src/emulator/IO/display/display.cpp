#include "display.hpp"
#include "../../../fonts/roboto.h"

Display::Display(SystemBus &bus) : IOInterface(bus){
    // this->displayBuffer = std::vector<std::vector<std::string>>(window.getSize().y, std::vector<std::string>(window.getSize().x, emptyChar));
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

    this->displayTexts.push_back({text, x, y});

    std::cout<<"Displaying text\n";

}

void Display::displayPixel(){
    // sf::RectangleShape pixel(sf::Vector2f(1, 1));
    // pixel.setFillColor(sf::Color::White);
    // pixel.setPosition(x, y);
    // window.draw(pixel);
    // this->displayBuffer[y][x] = "X";

    std::cout<<"Displaying pixel\n";

    Rectangle pixel = {x, y, 1, 1};

    this->displayRects.push_back(pixel);
}

void Display::clearDisplay(){
    ClearBackground(WHITE);
    // this->displayBuffer = std::vector<std::vector<std::string>>(window.getSize().y, std::vector<std::string>(window.getSize().x, emptyChar));
}

void Display::clearPixel(){

    for(int i = 0; i < displayRects.size(); i++){

        Rectangle rect = displayRects[i];

        if(rect.x == x && rect.y == y){
            displayRects.erase(displayRects.begin() + i);
            break;
        }
    }

    // this->displayBuffer[y][x] = emptyChar;
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
    }

    return 0;
}


void Display::displayLoop(){
    ClearBackground(WHITE);
    BeginDrawing();

    for(const auto& rect: displayRects){
        DrawRectangle(rect.x, rect.y, rect.width*(GetScreenWidth()/64), rect.height*(GetScreenHeight()/64), BLACK);
    }

    for(const auto& text: displayTexts){
        DrawText(text.text.c_str(), text.x, text.y, 20*(GetScreenHeight()/64), BLACK);
    }

    EndDrawing();
}