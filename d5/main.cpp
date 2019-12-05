#include "computer/Computer.h"
#include "computer/Instruction.h"
#include <iostream>

class Addition : public Instruction {
public:
    int opcode() { return 1; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        if (parameter_mode[1] == 1) {
            parameter.push_back(memory[instruction_ptr + 2]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 2]]);
        }

        std::cout << "|" << instruction_ptr << "|";
        for (int i : parameter_mode) {
            std::cout << i;
        } 
        std::cout << "|: [" << memory[instruction_ptr+3] << "] = [" << 
            memory[instruction_ptr + 1] << "] + [" 
            << memory[instruction_ptr + 2] << "]\n";
        memory[memory[instruction_ptr+3]] = parameter[0] + parameter[1];
        return instruction_ptr + parameter_count() + 1;
    }
};

class Multiplication : public Instruction {
    int opcode() { return 2; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        if (parameter_mode[1] == 1) {
            parameter.push_back(memory[instruction_ptr + 2]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 2]]);
        }

        std::cout << "|" << instruction_ptr << "|";
        for (int i : parameter_mode) {
            std::cout << i;
        } 
        std::cout << "|: [" << memory[instruction_ptr+3] << "] = [" << 
            memory[instruction_ptr + 1] << "] * [" 
            << memory[instruction_ptr + 2] << "]\n";
        memory[memory[instruction_ptr+3]] = parameter[0] * parameter[1];
        return instruction_ptr + parameter_count() + 1;
    }
};

class Input : public Instruction {
    int opcode() { return 3; }
    int parameter_count() { return 1; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::cout << "|" << instruction_ptr << "|";
        for (int i : parameter_mode) {
            std::cout << i;
        } 
        std::cout << "|: [" << memory[instruction_ptr+1] << "] := ";
        std::cin >> memory[memory[instruction_ptr+1]];
        
        return instruction_ptr + parameter_count() + 1;
    }
};

class Output : public Instruction {
    int opcode() { return 4; }
    int parameter_count() { return 1; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        std::cout << "|" << instruction_ptr << "|";
        for (int i : parameter_mode) {
            std::cout << i;
        } 
        std::cout << "|: "
            "[" << memory[instruction_ptr+1] << "] = " << 
            parameter[0] << "\n";        
        return instruction_ptr + parameter_count() + 1;
    }
};

class JMP_True : public Instruction {
    int opcode() { return 5; }
    int parameter_count() { return 2; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        if (parameter_mode[1] == 1) {
            parameter.push_back(memory[instruction_ptr + 2]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 2]]);
        }

        std::cout << "|" << instruction_ptr << "|: JMP to " << 
            "[" << parameter[1] << "] if " << parameter[0] << " true\n";
        if (parameter[0]) {
            return parameter[1];
        } else {
            return instruction_ptr + parameter_count() + 1;
        }
    }
};

class JMP_False : public Instruction {
    int opcode() { return 6; }
    int parameter_count() { return 2; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        if (parameter_mode[1] == 1) {
            parameter.push_back(memory[instruction_ptr + 2]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 2]]);
        }

        std::cout << "|" << instruction_ptr << "|: JMP to " << 
            "[" << parameter[1] << "] if " << parameter[0] << " false\n";
        if (!parameter[0]) {
            return parameter[1];
        } else {
            return instruction_ptr + parameter_count() + 1;
        }
    }
};

class Less : public Instruction {
    int opcode() { return 7; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        if (parameter_mode[1] == 1) {
            parameter.push_back(memory[instruction_ptr + 2]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 2]]);
        }

        std::cout << "|" << instruction_ptr << "|: " << 
            "[" << memory[instruction_ptr+3] << "] = " << parameter[0] << " < " << parameter[1] << "\n";
        
        memory[memory[instruction_ptr+3]] = parameter[0] < parameter[1];

        return instruction_ptr + parameter_count() + 1;
    }
};

class Equal : public Instruction {
    int opcode() { return 8; }
    int parameter_count() { return 3; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::vector<int> parameter;
        if (parameter_mode[0] == 1) {
            parameter.push_back(memory[instruction_ptr + 1]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 1]]);
        }

        if (parameter_mode[1] == 1) {
            parameter.push_back(memory[instruction_ptr + 2]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 2]]);
        }

        if (parameter_mode[2] == 1) {
            parameter.push_back(memory[instruction_ptr + 3]);
        } else {
            parameter.push_back(memory[memory[instruction_ptr + 3]]);
        }

        std::cout << "|" << instruction_ptr << "|: " << 
            "[" << memory[instruction_ptr+3] << "] = " << parameter[0] << " == " << parameter[1] << "\n";
        
        memory[memory[instruction_ptr+3]] = parameter[0] == parameter[1];

        return instruction_ptr + parameter_count() + 1;
    }
};

class Halt : public Instruction {
    int opcode() { return 99; }
    int parameter_count() { return 0; }

    int code(std::vector<int>& memory, int instruction_ptr, std::vector<int> parameter_mode) {
        std::cout << "|" << instruction_ptr << "|: HALT\n";
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