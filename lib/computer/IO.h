#ifndef IO_H
#define IO_H

#include "Instruction.h"
#include <iostream>

int nextInput = -1;
int lastOutput = -1;

class Input : public Instruction {
    int opcode() { return 3; }
    int parameter_count() { return 1; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "Input := ";
        if (parameter[0]->mode == 2) {
            std::cin >> memory[base_ptr + memory[instruction_ptr + 1]];
        } else {
            if (nextInput != -1) {
                std::cout << nextInput << "\n";
                memory[memory[instruction_ptr+1]] = nextInput;
                nextInput = -1;
            } else if (nextInput == -1 && lastOutput != -1) {
                std::cout << lastOutput << "\n";
                memory[memory[instruction_ptr+1]] = lastOutput;
                lastOutput = -1;
            } else {
                std::cin >> memory[memory[instruction_ptr+1]];
            }
        }
        
        
        return instruction_ptr + parameter_count() + 1;
    }
};

class Output : public Instruction {
    int opcode() { return 4; }
    int parameter_count() { return 1; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "= " << 
            parameter[0]->param << "\n";
        lastOutput = parameter[0]->param;
        return instruction_ptr + parameter_count() + 1;
    }
};

#endif