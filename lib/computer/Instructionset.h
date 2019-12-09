#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include "Instruction.h"
#include "IO.h"
#include "Math.h"
#include "Conditionals.h"
#include "Halt.h"
#include "Base.h"

#include <iostream>
#include <vector>

class InstructionSet {
private:
    std::vector<Instruction*> instruction_set_;
public:
    InstructionSet() {
        instruction_set_.push_back(new Addition());
        instruction_set_.push_back(new Multiplication());
        instruction_set_.push_back(new JMP_True());
        instruction_set_.push_back(new JMP_False());
        instruction_set_.push_back(new Less());
        instruction_set_.push_back(new Equal());
        instruction_set_.push_back(new Base());
        instruction_set_.push_back(new Output());
        instruction_set_.push_back(new Input());
        instruction_set_.push_back(new Halt());
    }

    void enable_all() {
        for (int i = 0; i < instruction_set_.size(); ++i) {
            instruction_set_[i]->enable();
        }
    }

    void enable(int opcode) {
        for (int i = 0; i < instruction_set_.size(); ++i) {
            if (instruction_set_[i]->opcode() == opcode) {
                instruction_set_[i]->enable();
                break;
            }
        }
    }

    void disable(int opcode) {
        for (int i = 0; i < instruction_set_.size(); ++i) {
            if (instruction_set_[i]->opcode() == opcode) {
                instruction_set_[i]->enable();
                break;
            }
        }
    }
    
    std::vector<Instruction*> get() {
        return instruction_set_;
    }
};

#endif