#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

#include "Instruction.h"

class Computer {
private:
    std::vector<int> memory_;
    std::vector<Instruction*> instruction_set_;
    int instruction_ptr_;
    bool halt_on_output_;
public:
    void printInstructionSet() {
        for (int i = 0; i < instruction_set_.size(); ++i) {
            std::cout << instruction_set_[i]->opcode() << ", ";
            if (instruction_set_[i]->enabled()) {
                std::cout << "enabled\n";
            } else {
                std::cout << "disabled\n";
            }
        }
    }

    Computer(std::vector<Instruction*> instruction_set, bool halt_on_output = false) : memory_(), instruction_set_(instruction_set), halt_on_output_(halt_on_output) {
        std::cout << " ~~~ Intcode Computer ~~~ \n";
        std::cout << "Booted up!\n";
    }

    void load_memory(std::vector<int> memory) {
        memory_.clear();
        instruction_ptr_ = 0;
        memory_ = memory;
    }

    void load_from_file(std::string filename) {
        std::ifstream input(filename);
        memory_.clear();
        instruction_ptr_ = 0;

        std::string code;
        while(std::getline(input, code, ',')) {
            memory_.push_back(std::stoi(code));
        }
    }

    int execute() {
        for (int j = 0; j < memory_.size(); ++j) {
            int exit_code = 0;
            for (int i = 0; i < instruction_set_.size(); ++i) {
                exit_code = instruction_set_[i]->execute(memory_, instruction_ptr_);
                if (exit_code == SUCCESSFUL_INSTRUCTION) {
                    if (instruction_set_[i]->opcode() == 4 && halt_on_output_) {
                        return 0;
                    }
                    break;
                } else if (exit_code == HALT_INSTRUCTION) {
                    return 0;
                }
            }
        }
        return 1;
    }

    void alter_memory(int new_value, int address) {
        memory_[address] = new_value;
    }

    int read_memory(int address) {
        return memory_[address];
    }

    std::vector<int> get_memory() {
        return memory_;
    }
};



#endif