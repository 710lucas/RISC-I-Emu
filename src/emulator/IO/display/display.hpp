#pragma once

#include "../IO.hpp"
#include "../../BUS/systemBus.hpp"
#include <vector>
#include <iostream>

class Display : public IOInterface{

    private:  
        //Display characters (vector)
        std::vector<std::vector<std::string>> displayBuffer;

        int x = 0;
        int y = 0;

        int displaySize = 64;
        std::string emptyChar = ".";

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
        virtual void read(long address) override;

        //Execute IO operation
        virtual byte execute(byte control, byte address, byte data) override;

        //Print display
        void printDisplay();

};