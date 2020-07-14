#include "computer/Computer.h"
#include "computer/Instructionset.h"

#include <iostream>
#include <vector>

int main() {
    InstructionSet instruction_set;
    instruction_set.enable_all();
    
    Computer com;
    com.load_from_file("inputs/d9.txt");

    instruction_set.execute(com);

    // GOAL: 63441
}
// Too low: 21107