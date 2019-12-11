#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "Instruction.h"
#include <iostream>

class JMP_True : public Instruction {
    int opcode() { return 5; }
    int parameter_count() { return 2; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        std::cout << parameter[0]->address << ", " << com.read_memory(parameter[0]->address) << "\n";
        if (com.read_memory(parameter[0]->address)) {
            return com.read_memory(parameter[1]->address);
        } else {
            return com.instruction_ptr_ + parameter_count() + 1;
        }
    }
};

class JMP_False : public Instruction {
    int opcode() { return 6; }
    int parameter_count() { return 2; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        if (!com.read_memory(parameter[0]->address)) {
            return com.read_memory(parameter[1]->address);
        } else {
            return com.instruction_ptr_ + parameter_count() + 1;
        }
    }
};

class Less : public Instruction {
    int opcode() { return 7; }
    int parameter_count() { return 3; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        com.alter_memory(com.read_memory(parameter[0]->address) < com.read_memory(parameter[1]->address), parameter[2]->address);

        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

class Equal : public Instruction {
    int opcode() { return 8; }
    int parameter_count() { return 3; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        com.alter_memory(com.read_memory(parameter[0]->address) == com.read_memory(parameter[1]->address), parameter[2]->address);

        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

#endif