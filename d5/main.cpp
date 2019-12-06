#include "computer/Computer.h"
#include "computer/Instruction.h"
#include "computer/Math.h"
#include "computer/IO.h"
#include "computer/Conditionals.h"

#include <iostream>

class Halt : public Instruction {
    int opcode() { return 99; }
    int parameter_count() { return 0; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<Parameter*>& parameter) {
        std::cout << "HALT\n";
        return HALT_INSTRUCTION;
    }
};

std::vector<Instruction*> instruction_set{
    new Addition(), 
    new Multiplication(), 
    new JMP_True(),
    new JMP_False(),
    new Less(),
    new Equal(),
    new Output(), 
    new Input(), 
    new Halt()
};

int main() {
    Computer com = Computer(instruction_set);
    com.load_from_file("inputs/d5.txt");
    com.execute();
}