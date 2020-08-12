#pragma once

#include <utility>
#include <vector>
#include <functional>
#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>

using opcode_t = int;

struct Memory {
    std::vector<opcode_t> mem;

    opcode_t &operator[](size_t index) {
        if (index >= mem.size()) {
            mem.resize(index);
        }
        return mem[index];
    }

    [[nodiscard]] std::size_t size() const {
        return mem.size();
    }
};

struct Instruction {
    opcode_t opcode;
    unsigned int parameter_count;
    std::function<bool()> exec;

    Instruction(opcode_t opcode, unsigned int parameter_count, std::function<bool()> exec)
            : opcode(opcode), parameter_count(parameter_count), exec(std::move(exec)) {};
};

class Computer {
public:
    Memory mem;
    std::size_t isp = 0;
    std::vector<Instruction> is;

    Computer() {
        is.emplace_back(99, 0, [&]() { return false; });
        is.emplace_back(1, 3, [&]() {
            mem[mem[isp + 3]] = mem[mem[isp + 1]] + mem[mem[isp + 2]];
            return true;
        });
        is.emplace_back(2, 3, [&]() {
            mem[mem[isp + 3]] = mem[mem[isp + 1]] * mem[mem[isp + 2]];
            return true;
        });
    }

    explicit Computer(Memory mem) : Computer() {
        this->mem = std::move(mem);
    };

    void load(const std::filesystem::path& path) {
        if (std::filesystem::is_regular_file(path)) {
            std::ifstream file(path, std::ios::in);
            if (file.good()) {
                std::string content;
                std::getline(file, content);

                for (std::size_t i = 0, start = 0; i < content.size(); ++i) {
                    if (content[i] == ',') {
                        mem.mem.push_back(std::stoi(content.substr(start, i -start)));
                        start = i + 1;
                    }
                    if (i == content.size() - 1) {
                        mem.mem.push_back(std::stoi(content.substr(start, i -start +1)));
                    }
                }
            } else {
                std::cout << "Not a good file: " << path <<"\n";
            }
        } else {
            std::cout << "Not a file: " << path << "\n";
        }
    }

    bool step() {
        if (mem.size() == 0) {
            return false;
        }
        for (auto &i : is) {
            if (i.opcode == mem[isp]) {
                if (!i.exec()) {
                    return false;
                } else {
                    isp += i.parameter_count + 1;
                }
            }
        }
        return true;
    }

    void execute() {
        if (mem.size() == 0) {
            return;
        }

        while (step()) {}
    }
};


