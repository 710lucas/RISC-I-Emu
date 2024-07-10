#pragma once

typedef unsigned char byte;

class ModuleInterface{

    public:
        virtual byte execute(byte control, byte address, byte data) = 0;

};