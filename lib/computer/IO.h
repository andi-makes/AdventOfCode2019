#ifndef IO_H
#define IO_H

#include "Instruction.h"
#include <iostream>

class Input : public Instruction {
    int opcode() { return 3; }
    int parameter_count() { return 1; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout <<  memory[instruction_ptr+1] << " := ";
        std::cin >> memory[memory[instruction_ptr+1]];
        
        return instruction_ptr + parameter_count() + 1;
    }
};

class Output : public Instruction {
    int opcode() { return 4; }
    int parameter_count() { return 1; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "[" << memory[instruction_ptr+1] << "] = " << 
            parameter[0]->param << "\n";        
        return instruction_ptr + parameter_count() + 1;
    }
};

#endif