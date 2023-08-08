package org.example;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

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

            System.out.printf("Somando "+a+" com "+ b+"\n");

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
            System.out.printf("sub "+a+" com "+ b+"\n");

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
            System.out.printf("and "+a+" com "+ b+"\n");
            registers[thirdOp] = ((a)&(b));
        }

        //OR
        else if(instruction == 0x07){
            System.out.printf("or "+a+" com "+ b+"\n");
            registers[thirdOp] = a|b;
        }

        //XOR
        else if(instruction == 0x08){
            System.out.printf("xor "+a+" com "+ b+"\n");
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

        //JMP
        else if(instruction == 0x13){
            if(registers[thirdOp] == 1) {
                pc = a + b - 1; //-1 considerando que pc será incrementado depois
                pc-=6; // Considerando ++ da proxima etapa
            }
        }

        //JMPR
        else if(instruction == 0x14){
            if(registers[thirdOp] == 1) {
                pc += a + b - 1; //-1 considerando que pc será incrementado depois
                pc-=6;// Considerando ++ da proxima etapa
            }
        }

        //CALL
        else if(instruction == 0x15){
            registers[thirdOp] = pc;
            pc = a+b;
            pc-=6; // Considerando ++ da proxima etapa
        }

        //Ret
        else if(instruction == 0x17){
            pc = a+b;
            pc-=6; // Considerando ++ da proxima etapa
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

    public static void loadMemory(String nomeArquivo){
        try {
            memory = Files.readAllBytes(Paths.get(nomeArquivo));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {

        pc = 0;
        String nomeArquivo;

        Scanner sc = new Scanner(System.in);

        if(args.length != 1) {
            System.out.print("Informe o nome do arquivo: ");
            nomeArquivo = sc.nextLine();
        }
        else
            nomeArquivo = args[0];

        loadMemory(nomeArquivo);

        while(pc<memory.length-5){
            executeInstruction(memory[pc]);




            pc+=6; // cada instrução tem 6 bytes, pula de 6 em 6
        }

        System.exit(0);
    }

}
