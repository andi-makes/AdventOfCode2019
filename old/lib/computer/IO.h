#ifndef IO_H
#define IO_H

#include "Instruction.h"
#include <iostream>

// int nextInput = -1;
// int lastOutput = -1;

bool enableISR = false;

int64_t (*inISR)(void);
void (*outISR)(int64_t);

class Input : public Instruction {
    int opcode() { return 3; }
    int parameter_count() { return 1; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        // std::cout << "Input := ";
        int64_t a = 0;
        if (enableISR) {
            a = inISR();
            // std::cout << a << "\n";
        } else {
            std::cout << "Input := ";
            std::cin >> a;
        }

        com.alter_memory(a, parameter[0]->address);

        // if (nextInput != -1) {
        //     std::cout << nextInput << "\n";
        //     com.alter_memory(nextInput, parameter[0]->address);
        //     nextInput = -1;
        // } else if (nextInput == -1 && lastOutput != -1) {
        //     std::cout << lastOutput << "\n";
        //     com.alter_memory(lastOutput, parameter[0]->address);
        //     lastOutput = -1;
        // } else {
        //     int64_t a;
        //     std::cin >> a;
        //     com.alter_memory(a, parameter[0]->address); 
        // }
    
        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

class Output : public Instruction {
    int opcode() { return 4; }
    int parameter_count() { return 1; }

    int code(Computer& com, std::vector<Parameter*>& parameter) {
        // std::cout << "= " << com.read_memory(parameter[0]->address) << "\n";
        int64_t output = com.read_memory(parameter[0]->address);
        if (enableISR) outISR(output);
        return com.instruction_ptr_ + parameter_count() + 1;
    }
};

#endif