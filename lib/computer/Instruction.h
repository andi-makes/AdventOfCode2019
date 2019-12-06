#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

#define SUCCESSFUL_INSTRUCTION 0
#define FAILED_INSTRUCTION -2
#define HALT_INSTRUCTION -1

class Parameter {
public:
    int param;

    Parameter(const std::vector<int>& memory, int instruction_ptr, int parameter_number, int parameter_count) {
        int opcode = memory[instruction_ptr];
        int possible = opcode / 100;

        int divider = std::pow(10, parameter_number);
        int mode = (possible / divider) % 10;

        if (mode == 1) {
            param = memory[instruction_ptr + parameter_number +1];
        } else {
            param = memory[memory[instruction_ptr + parameter_number+1]];
        }
    }
};

class Instruction {
private:
    bool isEnabled;
public:
    virtual int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) = 0;

    virtual int opcode() = 0;
    virtual int parameter_count() = 0;

    Instruction() : isEnabled(false) {}

    void enable() {
        isEnabled = true;
    }

    void disable() {
        isEnabled = false;
    }

    bool enabled() {
        return isEnabled;
    }

    int execute(std::vector<int>& memory, int& instruction_ptr) {
        if (isEnabled) {
            if (opcode() == memory[instruction_ptr] % 100) {
                std::vector<Parameter*> parameter;
                for (int i = 0; i < parameter_count(); ++i) {
                    parameter.push_back(new Parameter(memory, instruction_ptr, i, parameter_count()));
                }

                std::cout << "{ [" << std::setw(3) << instruction_ptr << "], " << std::setw(4) << memory[instruction_ptr] << " }: ";

                int ret = code(memory, instruction_ptr, parameter);
                if (ret < 0) {
                    return HALT_INSTRUCTION;
                } else {
                    instruction_ptr = ret;
                    return SUCCESSFUL_INSTRUCTION;
                }
            }
        }
        return FAILED_INSTRUCTION; 
    }
};

#endif