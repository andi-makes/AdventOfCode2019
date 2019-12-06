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

    Computer(std::vector<Instruction*> instruction_set) : memory_(), instruction_set_(instruction_set) {
        std::cout << " ~~~ Intcode Computer ~~~ \n";
        std::cout << "Booted up!\n";
        std::cout << "Commands: load [filename], enable [opcode], disable [opcode], run\n";
    }

    void load_memory(std::vector<int> memory) {
        memory_.clear();
        memory_ = memory;
    }

    void load_from_file(std::string filename) {
        std::ifstream input(filename);
        memory_.clear();

        std::string code;
        while(std::getline(input, code, ',')) {
            memory_.push_back(std::stoi(code));
        }
    }

    void execute() {
        int instruction_ptr = 0;
        for (int j = 0; j < memory_.size(); ++j) {
            int exit_code = 0;
            for (int i = 0; i < instruction_set_.size(); ++i) {
                exit_code = instruction_set_[i]->execute(memory_, instruction_ptr);
                if (exit_code == SUCCESSFUL_INSTRUCTION) {
                    break;
                } else if (exit_code == HALT_INSTRUCTION) {
                    break;
                }
            }
            if (exit_code == HALT_INSTRUCTION) {
                break;
            }
        }
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