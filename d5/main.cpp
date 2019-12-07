#include "computer/Computer.h"
#include "computer/Instructionset.h"

#include <iostream>

int main() {
    InstructionSet instruction_set;
    instruction_set.enable_all();

    Computer com = Computer(instruction_set.get());
    com.load_from_file("inputs/d5.txt");
    com.execute();
}