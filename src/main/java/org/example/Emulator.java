package org.example;

public class Emulator {

    private static int[] registers = new int[32];
    private static boolean carry = false; //Flag
    private static boolean print = false; //Flag

    private static int pc;

    private static byte[] memory = new byte[1024*1024*4]; //4 MB
    // 0x000000 0x0fffff -> stdout

    private static int ir;

    public static void executeInstruction(byte instruction){
        int firstOpLower, firstOpHigher, firstOp;
        int secondOpLower,secondOpHigher, secondOp;
        int thirdOp;

        firstOpLower = memory[pc+1] & 0xFF;
        firstOpHigher = memory[pc+2] & 0xFF;
        firstOp = ((firstOpLower) <<8) | firstOpHigher;

        secondOpLower = memory[pc+3] & 0xFF;
        secondOpHigher = memory[pc+4] & 0xFF;
        secondOp = (secondOpLower <<8) | secondOpHigher;

        thirdOp = memory[pc+5] & 0xFF;

        int a = getOperandValue(firstOpLower, firstOpHigher, 0x20);
        int b = getOperandValue(secondOpLower, secondOpHigher, 0x20);

        //                 ADD                    ADDC
        if(instruction  == 0x01 || instruction == 0x02){

            long correctvalue = a+b;

            registers[thirdOp] = a+b;

            if(instruction == 0x02) {
                registers[thirdOp]++;
                correctvalue++;
            }

            if(registers[thirdOp] != correctvalue) {
                carry = true;
                registers[thirdOp] = Integer.MAX_VALUE;
            }

        }

        // SUB                                        SUBC
        else if(instruction == 0x03 || instruction == 0x04){

            long correctValue = a-b;

            registers[thirdOp] = a-b;

            if(instruction == 0x04){
                registers[thirdOp]++;
                correctValue++;
            }

            if(registers[thirdOp] != correctValue){
                carry = true;
                registers[thirdOp] = Integer.MIN_VALUE;
            }
        }

        // AND
        else if(instruction == 0x06){
            registers[thirdOp] = a&b;
        }

        //OR
        else if(instruction == 0x07){
            registers[thirdOp] = a|b;
        }

        //XOR
        else if(instruction == 0x08){
            registers[thirdOp] = a^b;
        }

        //SLL Shift Left
        else if(instruction == 0x09){
            registers[thirdOp] = a << b;
        }

        //Right shift logical
        else if(instruction == 0x0a){
            registers[thirdOp] = a >>> b;
        }

        //Right shift A.
        else if(instruction == 0x0b){
            registers[thirdOp] = a >> b;
        }



    }


    public static int getOperandValue(int lower, int higher, int cap){
//        System.out.println("lower: "+lower);
//        System.out.println("higher: "+higher);

        if(lower>=cap)
            return higher;
        return registers[lower];
    }

    public static void main(String[] args) {
        pc = 0;
        memory[0]= 0x01;
        memory[1] = (byte)0xFF;
        memory[2] = (byte)0x0A;

        memory[3] = (byte)0xFF;
        memory[4] = (byte)0x01;

        memory[5] = (byte)0x00;

        executeInstruction(memory[pc]);

        System.out.println(registers[0]);


        registers[1] = 10;
        registers[2] = 1;

        memory[0]= 0x01;
        memory[1] = (byte)0x01;
        memory[2] = (byte)0x00;

        memory[3] = (byte)0x02;
        memory[4] = (byte)0x00;

        memory[5] = (byte)0x00;
        executeInstruction(memory[pc]);
        System.out.println(registers[0]);

        memory[0]= 0x03;
        memory[1] = (byte)0xFF;
        memory[2] = (byte)0x0A;

        memory[3] = (byte)0xFF;
        memory[4] = (byte)0x01;

        memory[5] = (byte)0x00;
        executeInstruction(memory[pc]);
        System.out.println(registers[0]);

        memory[0]= 0x06;
        memory[1] = (byte)0xFF;
        memory[2] = (byte)0b01111010;

        memory[3] = (byte)0xFF;
        memory[4] = (byte)0b00101010;

        memory[5] = (byte)0x00;
        executeInstruction(memory[pc]);
        System.out.println(Integer.toBinaryString(registers[0]));
    }

}
