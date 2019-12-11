#include "computer/Computer.h"
#include "computer/Instructionset.h"

#include <iostream>
#include <vector>

int main() {
    InstructionSet instruction_set;
    instruction_set.enable_all();
    nextInput = 2;
    Computer com = Computer(instruction_set.get());
    com.load_from_file("inputs/d9.txt");
    com.execute();

    // GOAL: 63441
}
// Too low: 21107