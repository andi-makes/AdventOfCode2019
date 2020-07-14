#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

class Computer {
private:
    std::vector<int64_t> memory_;
    bool halt_on_output_;
public:
    int instruction_ptr_;
    void expand_memory(int address) {
        for (int i = memory_.size(); i < address+1; ++i) {
            memory_.push_back(0);
        }
    }

    Computer(bool halt_on_output = false) : memory_(), halt_on_output_(halt_on_output) {
        std::cout << " ~~~ Intcode Computer ~~~ \n";
    }

    void load_memory(std::vector<int64_t> memory) {
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
            memory_.push_back(std::stoll(code));
        }
    }

    void alter_memory(int64_t new_value, int address) {
        if (address >= memory_.size())
            expand_memory(address);
        memory_[address] = new_value;
    }

    int64_t read_memory(int address) {
        if (address >= memory_.size())
            expand_memory(address);
        return memory_[address];
    }

    std::vector<int64_t>& get_memory() {
        return memory_;
    }
};

#endif