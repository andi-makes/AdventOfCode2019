#ifndef BASE_H
#define BASE_H

#include "Instruction.h"
#include <vector>

class Base : public Instruction {
    int opcode() { return 9; }
    int parameter_count() { return 1; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        base_ptr += parameter[0]->param;
        return instruction_ptr + parameter_count() + 1;
    }
};

#endif