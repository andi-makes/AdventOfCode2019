#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

// --- INTCODE INSTRUCTIONS --- //
#define INTCODE_ADDITION 1
#define INTCODE_MULTIPLICATION 2
#define INTCODE_HALT 99

/**
 * @brief Executes the given intcode
 * 
 * @param intcode is a std::vector<int>, are the instructions
 * @param no_output determines wheter the output is enabled or not. If true, output is supressed.
 * @return std::vector<int> the result of the intcode instructions
 */
std::vector<int> compute(std::vector<int> intcode, bool no_output = false) {
    for (int offset = 0; offset < intcode.size(); offset += 4) {
        switch (intcode[offset]) {
            case INTCODE_ADDITION:
                intcode[intcode[offset+3]] = intcode[intcode[offset + 1]] + intcode[intcode[offset + 2]];
                break;
            case INTCODE_MULTIPLICATION:
                intcode[intcode[offset+3]] = intcode[intcode[offset + 1]] * intcode[intcode[offset + 2]];
                break;
            case INTCODE_HALT:
                if (!no_output)
                    std::cout << "Encountered HALT expression.\nTerminating program.\n";
                return intcode;
                break;
            default:
                if (!no_output)
                    std::cout << "Encountered unknown expression `" << intcode[offset] << "` at position `" << offset << "`.\nTerminating program.\n";
                return intcode;
                break;
        }
    }
    return intcode;
}

/**
 * @brief Prints every element in a std::vector<int>
 * 
 * @param a vector to be print
 */
void printIntcode(std::vector<int> a) {
    for (int i = 0; i < a.size(); ++i) {
        std::cout << a[i];
        if (i + 1 != a.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";
}

/**
 * @brief loads a file named filename as intcode
 * 
 * @param filename file to be read
 * @return std::vector<int> content of file parsed as intcode
 */
std::vector<int> loadFile(std::string filename) {
    std::ifstream intcode_file(filename);

    std::vector<int> intc;
    while(!intcode_file.eof()) {
        static char c = 0;
        static std::vector<int> tmp;
        intcode_file.get(c);
        if (c == ',' || intcode_file.eof()) {
            int code = 0;
            for (int i = 0; i < tmp.size(); ++i) {
                code += std::pow(10, tmp.size()-1-i) * tmp[i];
            }
            tmp.clear();
            intc.push_back(code);
        } else {
            tmp.push_back(c - '0');
        }
    }

    intcode_file.close();
    
    return intc;
}

int main() {
    std::cout << "Intcode Computer - Day 2\n";
    {
        std::cout << "\n$ Part 1:\n";
        auto intc = loadFile("inputs/d2.txt");

        intc = compute(intc, true);
        std::cout << "Computed input. Result: \n";
        printIntcode(intc);
    };
    {
        std::cout << "\n$ Part 2:\n";
        for (int x = 0; x < 100; ++x) {
            for (int y = 0; y < 100; ++y) {
                auto intc = loadFile("inputs/d2.txt");
                intc[1] = x;
                intc[2] = y;
                intc = compute(intc, true);
                if (intc[0] == 19690720) {
                    std::cout << "Got the result: " << x * 100 + y << "\n";
                    return 0;
                }
            }
        }
    };   
}