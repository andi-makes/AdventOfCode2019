#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>

#define SUCCESSFUL_INSTRUCTION 0
#define FAILED_INSTRUCTION -2
#define HALT_INSTRUCTION -1

class Instruction {
public:
    virtual int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) = 0;

    virtual int opcode() = 0;
    virtual int parameter_count() = 0;

    int execute(std::vector<int>& memory, int& instruction_ptr) {
        if (opcode() == memory[instruction_ptr] % 100) {

            int possible = memory[instruction_ptr] / 100;
            std::vector<int> parameter_modes;
            for (int i = 1; i <= possible; i *= 10) {
                if (possible / i % 10) {
                    parameter_modes.push_back(1);
                } else {
                    parameter_modes.push_back(0);
                }
            }

            for (int i = parameter_modes.size(); i < parameter_count(); ++i) {
                parameter_modes.push_back(0);
            }

            int ret = code(memory, instruction_ptr, parameter_modes);
            if (ret < 0) {
                return HALT_INSTRUCTION;
            } else {
                instruction_ptr = ret;
            }
        }
        return FAILED_INSTRUCTION;
    }
};

#endif