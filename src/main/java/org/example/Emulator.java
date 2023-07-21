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

            if(instruction == 0x02 && carry) {
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

            if(instruction == 0x04 && carry){
                registers[thirdOp]--;
                correctValue--;
            }

            if(registers[thirdOp] != correctValue){
                carry = true;
                registers[thirdOp] = Integer.MIN_VALUE;
            }
        }

        // AND
        else if(instruction == 0x06){
            registers[thirdOp] = ((a)&(b));
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

        // LDL
        else if(instruction == 0x0c){

            byte[] by = {memory[a+b], memory[a+b+1], memory[a+b+2], memory[a+b+3]};
            registers[thirdOp] = bytesToInt(by);

        }

        //STL
        else if(instruction == 0x10){
//            memory[a+b] = registers[thirdOp];
            byte[] bytes = intToBytes(registers[thirdOp]);
            for(int i = 0; i<bytes.length; i++){
                memory[a+b+i] = bytes[i];
            }
        }


    }

    public static byte[] intToBytes(int integer){
        byte[] out = new byte[4];
        out[0] = (byte)((integer >> 24)&0xFF);
        out[1] = (byte)((integer >> 16)&0xFF);
        out[2] = (byte)((integer >> 8)&0xFF);
        out[3] = (byte)(integer&0xFF);
        return out;
    }

    public static int bytesToInt(byte[] bytes) {
        int out = bytes[0];
        for(int i = 1; i<bytes.length; i++){
            out = out<<8;
            out = out| (bytes[i]);
        }
        return out;
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


        /*                  ADD                 */
        memory[0] = 0x01;

        //Primeiro operando
        memory[1] = (byte) 0xFF;
        memory[2] = 10;

        //Segundo operando
        memory[3] = (byte) 0xFF;
        memory[4] = 5;

        //Terceiro operando (em qual registrador será salvo a soma)
        memory[5] = 0;
        executeInstruction(memory[pc]);
        System.out.println("A adição entre 10 e 5 é: "+registers[0]);
        //==============================================================


        /*                  SUB                 */
        memory[0] = 0x03;

        //Primeiro operando
        memory[1] = (byte) 0xFF;
        memory[2] = 10;

        //Segundo operando
        memory[3] = (byte) 0xFF;
        memory[4] = 5;

        //Terceiro operando (em qual registrador será salvo a subtração)
        memory[5] = 1;
        executeInstruction(memory[pc]);
        System.out.println("A subtração entre 10 e 5 é: "+registers[1]);
        //==============================================================

        /*                  AND                 */
        memory[0] = 0x06;

        //Primeiro operando
        memory[1] = (byte) 0x20;
        memory[2] = 0b00010100;

        //Segundo operando
        memory[3] = (byte) 0x20;
        memory[4] = 0b00011100;

        //Terceiro operando (em qual registrador será salvo a operação entre o primeiro&segundo)
        memory[5] = 10;
        executeInstruction(memory[pc]);
        System.out.println("A operação and resultou em: "+ Integer.toBinaryString(registers[10]));
        //==============================================================


        /*                  OR                 */
        memory[0] = 0x07;

        //Primeiro operando
        memory[1] = (byte) 0x20;
        memory[2] = 0b00010100;

        //Segundo operando
        memory[3] = (byte) 0x20;
        memory[4] = 0b00011100;

        //Terceiro operando (em qual registrador será salvo a operação entre primeiro|segundo)
        memory[5] = 10;
        executeInstruction(memory[pc]);
        System.out.println("A operação and resultou em: "+ Integer.toBinaryString(registers[10]));
        //==============================================================

        /*                  STL - STORE                 */
        registers[1] = 69;
        memory[0] = 0x10;

        //Primeiro operando
        memory[1] = (byte) 0xFF;
        memory[2] = 14;

        //Segundo operando
        memory[3] = (byte) 0xFF;
        memory[4] = 1;

        //Primeiro operando e segundo operando serão somados para indicar o lugar da memória onde
        //será armazenado o valor no registrador no terceiro operando

        //Terceiro operando
        memory[5] = 1;
        executeInstruction(memory[pc]);


        //==============================================================

        /*                  LDL - LOAD                 */
        memory[0] = 0x0c;

        //Primeiro operando
        memory[1] = (byte) 0x20;
        memory[2] = 13;

        //Segundo operando
        memory[3] = (byte) 0x20;
        memory[4] = 2;

        //Terceiro operando (em qual registrador será salvo os dados em registradores[primeiro+segundo])
        memory[5] = 10;
        executeInstruction(memory[pc]);
        System.out.println("A operação and resultou em: "+ (registers[10]));
        //==============================================================



    }

}
