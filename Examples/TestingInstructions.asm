//This is a simple program to test every Instruction and make sure its working

//byte 0
//Adding 5 to register 0
ADD 0xFF05 0xFF00 0x00

//byte 6
//Printing the register 0
PRNT 0x0000 0x0000 0x00

//byte 12
//Subtracting 6 from register 0 and storing on register 01
SUB 0x0000 0xFF06 0x01

//byte 18
//Checking if register 0 is the same
PRNT 0x0000 0x0000 0x00

//byte 24
//Checking if regiser 1 is correct
PRNT 0x0000 0x0000 0x01

//byte 30
//AND instruction between 0x01 and 0x03, should result in 0x01
//Storing result on register 3
AND 0xFF01 0xFF03 0x03

//byte 36
//Checking if AND operation was succesful
PRNT 0x0000 0x0000 0x03

//byte 42
//OR instruction between 0x01 and 0x03, should result in 0x03
//Will be using the register 3 to make reference to 0x01 just to check if its working
//Storing result on register 3
OR 0x0300 0xFF03 0x03

//btye 48
//Checking if OR operation was succesful
PRNT 0x0000 0x0000 0x03

//byte 54 (sorry if the byte number is wrong, i'm bad at math)
//XOR instruction between 0x01 and 0x03, should result in 0x02
//I'll be using the register 3 as 0x03 just to check if its working
//Storing result on register 3
XOR 0xFF01 0x0300 0x03

//byte 60
//Checking if XOR operation was succesful
PRNT 0x0000 0x0000 0x03

//byte 66
//SLL, shifting 0x02 by 2 bits to the left, should result in 0x08
//Storing the result on register 4
SLL 0xFF02 0xFF02 0x04

//byte 72
//Checking if SLL was succesful
PRNT 0x0000 0x0000 0x04

//byte 78
//SRL, Shifting 0x02 by 1 bits to the right, should result in 0x01
//Storing the result on register 4
SRL 0xFF02 0xFF01 0x04

//byte 84
//Checking if SRL was succesful
PRNT 0x0000 0x0000 0x04

//byte 90
//LDL, loading a value from memory
//Storing result on register 5
//Should load the value 5, since 5 is the third byte we load into memory
//5 is loaded from our first instruction, so byte[0] = 0x01 (ADD = 0x01),
//byte[1] = 0xFF and byte[2] = 0x05
LDL 0xFF02 0xFF00 0x05

//byte 96
//Checking if LDL was succesful
PRNT 0x0000 0x0000 0x05

//byte 102
//STL, storing a value in memory
//Storing 0x2A (42) on the register 6
//then storing 0x2A in memory
ADD 0xFF2A 0xFF00 0x06

//byte 108
//Storing in value 400 of memory, C8 + C8, since a simple byte can't go up to 400, C8 = 200
STL 0xFFC8 0xFFC8 0x06

//byte 114
//Loading and then printing to check if STL was succesful
//Storing value on 0x07
LDL 0xFFC8 0xFFC8 0x07

//byte 120
//Checking if STL was succesful
PRNT 0x0000 0x0000 0x07

//byte 126
//Testing JMP
//I'll add 1 to the register 08 (which has the value 0)
//then I'll print the value on register 08
//If the register 08 is 1, then it'll jump here, adding 1 again
//and checking if register 08 is 1 again, if its working correctly
//it should jump, add 1, resulting in 2, priting 2 and not jumping again
ADD 0xFF01 0x0800 0x08

//byte 132
PRNT 0x0000 0x0000 0x08

//byte 138
//0x7E is 126, the byte we want to jump back
JMP 0xFF7E 0xFF00 0x08

//byte 144
//Testing JMPR
//We cannot jump using negative numbers
//I'll print the register 8, then if its 1, i'll
//jump and then subtract and print 0, 
//if its not 1, i'll subtract again
//and go back to the JMPR
PRNT 0x0000 0x0000 0x08

//byte 150
JMPR 0xFF0C 0xFF0C 0x08

//byte 156
SUB 0x0800 0xFF01 0x08

//byte 162
PRNT 0x0000 0x0000 0x08

//byte 168
JMP 0xFF96 0xFF00 0x08

//byte 174
SUB 0x0800 0xFF01 0x08

//byte 180
PRNT 0x0000 0x0000 0x08

//byte 186
//Preparing the call Instruction
//adding 10 to the register 16
//So it can be subtracted and jumping when it has
//the value 1
ADD 0xFF0A 0xFF00 0x10

//byte 192
//Testing CALL
//Will Call the line that returns, the return print the line again, causing a loop
//Will store the current position in register 10
CALL 0xFFD8 0xFF00 0x0A

//byte 198
//Printing 0x0A
PRNT 0x0000 0x0000 0x0A

//byte 204
//Subtracting from register 16
SUB 0x1000 0xFF01 0x10

//byte 210
JMP 0xFFDE 0xFF00 0x10

//byte 216
//Returning
RET 0x0A00 0xFF00 0x00

//byte 222
//Printing the value in register 10
PRNT 0x0000 0x0000 0x10

