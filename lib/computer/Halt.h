#ifndef HALT_H
#define HALT_H

#include "Instruction.h"

class Halt : public Instruction {
    int opcode() { return 99; }
    int parameter_count() { return 0; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "HALT\n";
        return HALT_INSTRUCTION;
    }
};

#endif