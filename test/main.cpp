#include "computer/Computer.h"
#include "computer/Instruction.h"
#include <iostream>

class Addition : public Instruction {
public:
    int opcode() { return 1; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr) {
        std::cout << "|" << instruction_ptr << "|: " <<
            "[" << memory[instruction_ptr+3] << "] = [" << 
            memory[instruction_ptr + 1] << "] + [" 
            << memory[instruction_ptr + 2] << "]\n";
        memory[memory[instruction_ptr+3]] = memory[memory[instruction_ptr + 1]] + memory[memory[instruction_ptr + 2]];
        return SUCCESSFUL_INSTRUCTION;
    }
};

class Multiplication : public Instruction {
    int opcode() { return 2; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr) {
        std::cout << "|" << instruction_ptr << "|: " <<
            "[" << memory[instruction_ptr+3] << "] = [" << 
            memory[instruction_ptr + 1] << "] * [" 
            << memory[instruction_ptr + 2] << "]\n";
        memory[memory[instruction_ptr+3]] = memory[memory[instruction_ptr + 1]] * memory[memory[instruction_ptr + 2]];
        return SUCCESSFUL_INSTRUCTION;
    }
};

class Halt : public Instruction {
    int opcode() { return 99; }
    int parameter_count() { return 0; }

    int code(std::vector<int>& memory, int instruction_ptr) {
        std::cout << "|" << instruction_ptr << "|: HALT\n";
        return HALT_INSTRUCTION;
    }
};

std::vector<Instruction*> instruction_set{new Addition(), new Multiplication(), new Halt()};

int main() {
    Computer com = Computer(instruction_set);
    com.load_from_file("inputs/d2.txt");
    com.execute();

    std::cout << (com.read_memory(0) == 5110675) << "\n";
}