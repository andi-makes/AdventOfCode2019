#include "computer/Computer.h"
#include "computer/Instructionset.h"
#include <iostream>

int main() {
    InstructionSet instruction_set;
    instruction_set.enable_all();
    Computer com = Computer(instruction_set.get());

    while (true) {
        static std::string command;
        std::cout << "$ (Note: It does nothing right now ;D)";
        std::getline(std::cin, command);
        std::cout << command;
    }

    
    com.execute();
}