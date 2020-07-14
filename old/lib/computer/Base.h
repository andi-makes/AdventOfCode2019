#ifndef BASE_H
#define BASE_H

#include "Instruction.h"
#include <vector>

class Base : public Instruction {
    int opcode() { return 9; }
    int parameter_count() { return 1; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        base_ptr += com.read_memory(parameter[0]->address);
        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

#endif