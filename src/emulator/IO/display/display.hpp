#pragma once

#include "../IO.hpp"
#include "../../BUS/systemBus.hpp"
#include <vector>
#include <iostream>
#include "raylib.h"

struct Text{
    std::string text;
    int x;
    int y;
};


class Display : public IOInterface{

    private:  
        std::vector<Rectangle> displayRects;
        std::vector<Text> displayTexts;

        int x = 0;
        int y = 0;


    public:
        Display(SystemBus &bus); 

        void displayText(byte address, byte size);

        void displayPixel();

        void clearDisplay();

        void clearPixel();

        void setX(int x);
        void setY(int y);

        //Write to display
        virtual void write(byte data) override;

        //Read from display
        virtual void read(int data, long address) override;

        //Execute IO operation
        virtual byte execute(byte control, byte address, byte data) override;

        void displayLoop();

};