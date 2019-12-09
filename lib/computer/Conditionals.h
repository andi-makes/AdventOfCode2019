#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "Instruction.h"
#include <iostream>

class JMP_True : public Instruction {
    int opcode() { return 5; }
    int parameter_count() { return 2; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        if (memory[parameter[0]->address]) {
            return memory[parameter[1]->address];
        } else {
            return instruction_ptr + parameter_count() + 1;
        }
    }
};

class JMP_False : public Instruction {
    int opcode() { return 6; }
    int parameter_count() { return 2; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        if (!memory[parameter[0]->address]) {
            return memory[parameter[1]->address];
        } else {
            return instruction_ptr + parameter_count() + 1;
        }
    }
};

class Less : public Instruction {
    int opcode() { return 7; }
    int parameter_count() { return 3; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        memory[parameter[2]->address] = memory[parameter[0]->address] < memory[parameter[1]->address];

        return instruction_ptr + parameter_count() + 1;
    }
};

class Equal : public Instruction {
    int opcode() { return 8; }
    int parameter_count() { return 3; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        memory[parameter[2]->address] = memory[parameter[0]->address] == memory[parameter[1]->address];

        return instruction_ptr + parameter_count() + 1;
    }
};

#endif