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
        int firstOpLower, firstOpHigher, firstOp,
            secondOpLower,secondOpHigher, secondOp,
            thirdOp;
        firstOpLower = memory[pc+1] & 0xFF;
        firstOpHigher = memory[pc+2] & 0xFF;
        firstOp = ((firstOpLower) <<8) | firstOpHigher;

        secondOpLower = memory[pc+3] & 0xFF;
        secondOpHigher = memory[pc+4] & 0xFF;
        secondOp = (secondOpLower <<8) | secondOpHigher;
        thirdOp = memory[pc+5] & 0xFF;

        switch (instruction){
            case 0x01: // ADD
//                firstOp = ((memory[pc+1] & 0xFF)<<8) | (memory[pc+2] & 0xFF); //0xFF -> 0xFF00
                int a, b;

                // Use value if a register isn't specified
                if(firstOpLower >= 0x20)
                    a = firstOpHigher;
                else
                    a = registers[firstOpLower];

                if(secondOpLower >= 0x20)
                    b = secondOpHigher;
                else
                    b = registers[secondOpLower];

                long correctvalue = a+b;

                registers[thirdOp] = a+b;
                if(a+b != correctvalue) {
                    carry = true;
                    registers[thirdOp] = Integer.MAX_VALUE;
                }

        }
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
        System.out.println(registers[0]);
    }

}
