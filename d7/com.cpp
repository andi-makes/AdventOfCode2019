#include "computer/Computer.h"
#include "computer/Instructionset.h"
#include <iostream>

int main() {
    InstructionSet instruction_set;
    instruction_set.enable_all();
    Computer ampA = Computer(instruction_set.get());
    Computer ampB = Computer(instruction_set.get());
    Computer ampC = Computer(instruction_set.get());
    Computer ampD = Computer(instruction_set.get());
    Computer ampE = Computer(instruction_set.get());
    int highest = 0;
    for (int a = 0; a < 5; ++a) {
        for (int b = 0; b < 5; ++b) {
            for (int c = 0; c < 5; ++c) {
                for (int d = 0; d < 5; ++d) {
                    for (int e = 0; e < 5; ++e) {
                        if (a != b && a != c && a != d && a != e) {
                            if (b != c && b != d && b != e) {
                                if (c != d && c != e) {
                                    if (d != e) {
                                        // std::cerr << "AROUND\n";
                                        ampA.load_from_file("inputs/d7.txt");
                                        ampB.load_from_file("inputs/d7.txt");
                                        ampC.load_from_file("inputs/d7.txt");
                                        ampD.load_from_file("inputs/d7.txt");
                                        ampE.load_from_file("inputs/d7.txt");
                                        lastOutput = 0;
                                        nextInput = -1;
                                        nextInput = a;
                                        ampA.execute();
                                        nextInput = b; // Comes from computer/IO.h
                                        ampB.execute();
                                        nextInput = c; // Comes from computer/IO.h
                                        ampC.execute();
                                        nextInput = d; // Comes from computer/IO.h
                                        ampD.execute();
                                        nextInput = e; // Comes from computer/IO.h
                                        ampE.execute();
                                        if (lastOutput > highest) {
                                            highest = lastOutput;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << "Highest Number: " << highest << "\n";
    std::cout << "Part 2:\n";
    highest = 0;
    for (int a = 5; a < 10; ++a) {
        for (int b = 5; b < 10; ++b) {
            for (int c = 5; c < 10; ++c) {
                for (int d = 5; d < 10; ++d) {
                    for (int e = 5; e < 10; ++e) {
                        if (a != b && a != c && a != d && a != e) {
                            if (b != c && b != d && b != e) {
                                if (c != d && c != e) {
                                    if (d != e) {
                                        // std::cerr << "AROUND\n";
                                        ampA.load_from_file("inputs/d7.txt");
                                        ampB.load_from_file("inputs/d7.txt");
                                        ampC.load_from_file("inputs/d7.txt");
                                        ampD.load_from_file("inputs/d7.txt");
                                        ampE.load_from_file("inputs/d7.txt");
                                        // std::vector<int> code = {3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5};
                                        // ampA.load_memory(code);
                                        // ampB.load_memory(code);
                                        // ampC.load_memory(code);
                                        // ampD.load_memory(code);
                                        // ampE.load_memory(code);
                                        lastOutput = 0;
                                        // nextInput = -1;
                                        int running = 1;
                                        while(running) {
                                            std::cerr << "Running..." << "\n";
                                            nextInput = a;
                                            // nextInput = 9;
                                            ampA.execute();
                                            nextInput = b; // Comes from computer/IO.h
                                            // nextInput = 8; // Comes from computer/IO.h
                                            ampB.execute();
                                            nextInput = c; // Comes from computer/IO.h
                                            // nextInput = 7; // Comes from computer/IO.h
                                            ampC.execute();
                                            nextInput = d; // Comes from computer/IO.h
                                            // nextInput = 6; // Comes from computer/IO.h
                                            ampD.execute();
                                            nextInput = e; // Comes from computer/IO.h
                                            // nextInput = 5; // Comes from computer/IO.h
                                            running = ampE.execute();
                                        }
                                        std::cerr << "Finished Running!\n";
                                        if (lastOutput > highest) {
                                            highest = lastOutput;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << "Highest: " << highest << "\n";
    // Too high: 680366614
    // Too high: 591944528
}