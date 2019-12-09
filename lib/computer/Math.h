#ifndef MATH_H
#define MATH_H

#include "Instruction.h"
#include <iostream>

class Addition : public Instruction {
public:
    int opcode() { return 1; }
    int parameter_count() { return 3; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        memory[parameter[2]->address] = memory[parameter[0]->address] + memory[parameter[1]->address];
        return instruction_ptr + parameter_count() + 1;
    }
};

class Multiplication : public Instruction {
    int opcode() { return 2; }
    int parameter_count() { return 3; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        memory[parameter[2]->address] = memory[parameter[0]->address] * memory[parameter[1]->address];
        return instruction_ptr + parameter_count() + 1;
    }
};

#endif