#ifndef HALT_H
#define HALT_H

#include "Instruction.h"

class Halt : public Instruction {
    int opcode() { return 99; }
    int parameter_count() { return 0; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        return HALT_INSTRUCTION;
    }
};

#endif