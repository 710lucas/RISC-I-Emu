#include "stack.h"

Stack::Stack(){
    this->stack = std::vector<int>();
}

void Stack::push(int value){
    this->stack.push_back(value);
}

int Stack::pop(){
    int value = this->stack.back();
    this->stack.pop_back();
    return value;
}

int Stack::peek(){
    return this->stack.back();
}

int Stack::size(){
    return this->stack.size();
}
