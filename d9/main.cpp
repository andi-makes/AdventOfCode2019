#include "computer/Computer.h"
#include "computer/Instructionset.h"

#include <iostream>
#include <vector>

int main() {
    InstructionSet instruction_set;
    instruction_set.enable_all();

    Computer com = Computer(instruction_set.get());
    // std::vector<int64_t> code{1102,34915192,34915192,7,4,7,99,0};
    // com.load_memory(code);
    com.load_from_file("inputs/d9.txt");
    com.execute();
}
// Too low: 21107