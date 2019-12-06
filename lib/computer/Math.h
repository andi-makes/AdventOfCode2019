#ifndef MATH_H
#define MATH_H

#include "Instruction.h"
#include <iostream>

class Addition : public Instruction {
public:
    int opcode() { return 1; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "[" << memory[instruction_ptr+3] << "] = [" << 
            memory[instruction_ptr + 1] << "] + [" 
            << memory[instruction_ptr + 2] << "]\n";
        memory[memory[instruction_ptr+3]] = parameter[0]->param + parameter[1]->param;
        return instruction_ptr + parameter_count() + 1;
    }
};

class Multiplication : public Instruction {
    int opcode() { return 2; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "[" << memory[instruction_ptr+3] << "] = [" << 
            memory[instruction_ptr + 1] << "] * [" 
            << memory[instruction_ptr + 2] << "]\n";
        memory[memory[instruction_ptr+3]] = parameter[0]->param * parameter[1]->param;
        return instruction_ptr + parameter_count() + 1;
    }
};

#endif