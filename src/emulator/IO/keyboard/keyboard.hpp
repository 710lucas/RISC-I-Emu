#pragma once

#include "../IO.hpp"

class Keyboard : public IOInterface{

    private:
        int pressedKey = 0;

    public:
        Keyboard(SystemBus &bus);

        //Write to keyboard
        virtual void write(byte data) override;

        //Read from keyboard
        virtual void read(long address) override;

        //Execute IO operation
        virtual byte execute(byte control, byte address, byte data) override;

        void keyboardLoop();

};