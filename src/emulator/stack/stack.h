#pragma once
#include <vector>

class Stack {

    private : 
        std::vector<int> stack;

    public :
        Stack();
        void push(int value);
        int pop();
        int peek();
        int size();

};