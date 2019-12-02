#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define INTCODE_ADDITION 1
#define INTCODE_MULTIPLICATION 2
#define INTCODE_HALT 99

#define RETURNCODE_COMPLETED 0
#define RETURNCODE_UNKNOWN_EXPRESSION 1

std::vector<int> compute(std::vector<int> intcode) {
    for (int offset = 0; offset < intcode.size(); offset += 4) {
        switch (intcode[offset]) {
            case INTCODE_ADDITION:
                intcode[intcode[offset+3]] = intcode[intcode[offset + 1]] + intcode[intcode[offset + 2]];
                break;
            case INTCODE_MULTIPLICATION:
                intcode[intcode[offset+3]] = intcode[intcode[offset + 1]] * intcode[intcode[offset + 2]];
                break;
            case INTCODE_HALT:
                std::cout << "Encountered HALT expression.\nTerminating program.\n";
                return intcode;
                break;
            default:
                std::cout << "Encountered unknown expression `" << intcode[offset] << "` at position `" << offset << "`.\nTerminating program.\n";
                return intcode;
                break;
        }
    }
    return intcode;
}

void printIntcode(std::vector<int> a) {
    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i + 1 != a.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

std::vector<int> loadFile(std::string filename) {
    std::ifstream intcode_file("input.txt");

    std::vector<int> intc;
    while(!intcode_file.eof()) {
        static char c = 0;
        static std::vector<int> tmp;
        intcode_file.get(c);
        if (c == ',' || intcode_file.eof()) {
            int code = 0;
            for (int i = 0; i < tmp.size(); ++i) {
                // std::cout << tmp[i] << ", ";
                code += std::pow(10, tmp.size()-1-i) * tmp[i];
            }
            // std::cout << code << "\n";
            tmp.clear();
            intc.push_back(code);
        } else {
            tmp.push_back(c - '0');
        }
    }

    return intc;
    
    intcode_file.close();
}

int main() {
    std::cout << "Intcode Computer - Day 2\n";

    
    // auto intc = loadFile("input.txt");

    // printIntcode(intc);
    // intc = compute(intc);

    for (int x = 0; x < 100; ++x) {
        for (int y = 0; y < 100; ++y) {
            auto intc = loadFile("input.txt");
            intc[1] = x;
            intc[2] = y;
            intc = compute(intc);
            if (intc[0] == 19690720) {
                std::cout << "Got the result: " << x * 100 + y << "\n";
                return 0;
            }
        }
    }

    std::cout << "Computed input. Result: ";
    // printIntcode(intc);
}