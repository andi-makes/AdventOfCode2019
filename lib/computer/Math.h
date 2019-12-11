#ifndef MATH_H
#define MATH_H

#include "Instruction.h"
#include <iostream>

class Addition : public Instruction {
public:
    int opcode() { return 1; }
    int parameter_count() { return 3; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        com.alter_memory(com.read_memory(parameter[0]->address) + com.read_memory(parameter[1]->address), parameter[2]->address);
        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

class Multiplication : public Instruction {
    int opcode() { return 2; }
    int parameter_count() { return 3; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        com.alter_memory(com.read_memory(parameter[0]->address) * com.read_memory(parameter[1]->address), parameter[2]->address);
        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

#endif