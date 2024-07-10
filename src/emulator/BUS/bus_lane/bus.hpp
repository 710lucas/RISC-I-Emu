#pragma once

typedef unsigned char byte;
typedef short twoBytes;

class Bus{

    // 1 Byte

    private:
        byte value;

    public:
        Bus();
        byte read();
        void write(byte value);

};