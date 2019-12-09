#ifndef CONDITIONALS_H
#define CONDITIONALS_H

#include "Instruction.h"
#include <iostream>

class JMP_True : public Instruction {
    int opcode() { return 5; }
    int parameter_count() { return 2; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        // std::cout << "JMP to " << 
            // "[" << parameter[1]->param << "] if " << parameter[0]->param << " true\n";
        if (parameter[0]->param) {
            return parameter[1]->param;
        } else {
            return instruction_ptr + parameter_count() + 1;
        }
    }
};

class JMP_False : public Instruction {
    int opcode() { return 6; }
    int parameter_count() { return 2; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        // std::cout << "JMP to " << 
        //     "[" << parameter[1]->param << "] if " << parameter[0]->param << " false\n";
        if (!parameter[0]->param) {
            return parameter[1]->param;
        } else {
            return instruction_ptr + parameter_count() + 1;
        }
    }
};

class Less : public Instruction {
    int opcode() { return 7; }
    int parameter_count() { return 3; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        // std::cout << "[" << memory[instruction_ptr+3] << "] = " << parameter[0]->param <<
        //     " < " << parameter[1]->param << "\n";
        
        if (parameter[2]->mode == 2) {
            memory[base_ptr + memory[instruction_ptr+3]] = parameter[0]->param < parameter[1]->param;
        } else {
            memory[memory[instruction_ptr+3]] = parameter[0]->param < parameter[1]->param;
        }

        return instruction_ptr + parameter_count() + 1;
    }
};

class Equal : public Instruction {
    int opcode() { return 8; }
    int parameter_count() { return 3; }

    int code(std::vector<int64_t>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        // std::cout << "[" << memory[instruction_ptr+3] << "] = " << parameter[0]->param << 
        //     " == " << parameter[1]->param << "\n";
        
        if (parameter[2]->mode == 2) {
            memory[base_ptr + memory[instruction_ptr+3]] = parameter[0]->param == parameter[1]->param;
        } else 
            memory[memory[instruction_ptr+3]] = parameter[0]->param == parameter[1]->param;

        return instruction_ptr + parameter_count() + 1;
    }
};

#endif