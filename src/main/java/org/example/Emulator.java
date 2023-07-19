package org.example;

public class Emulator {

    private static int[] registers = new int[32];
    private static boolean carry = false; //Flag
    private static boolean print = false; //Flag

    private static int pc;

    private static byte[] memory = new byte[1024*1024*4]; //4 MB
    // 0x000000 0x0fffff -> stdout

    private static int ir;

    public static void main(String[] args) {

    }

}
