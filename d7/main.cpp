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
    nextInput = -1;
    lastOutput = 0;
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
    std::cout << "With the help of this reddit post: https://www.reddit.com/r/adventofcode/comments/e7aqcb/2019_day_7_part_2_confused_with_the_question/";
    highest = 0;
    nextInput = -1;
    lastOutput = -1;
    for (int a = 5; a < 10; ++a) {
        for (int b = 5; b < 10; ++b) {
            for (int c = 5; c < 10; ++c) {
                for (int d = 5; d < 10; ++d) {
                    for (int e = 5; e < 10; ++e) {
                        if (a != b && a != c && a != d && a != e) {
                            if (b != c && b != d && b != e) {
                                if (c != d && c != e) {
                                    if (d != e) {
                                        Computer coma = Computer(instruction_set.get(), true);
                                        Computer comb = Computer(instruction_set.get(), true);
                                        Computer comc = Computer(instruction_set.get(), true);
                                        Computer comd = Computer(instruction_set.get(), true);
                                        Computer come = Computer(instruction_set.get(), true);
                                        
                                        coma.load_from_file("inputs/d7.txt");
                                        comb.load_from_file("inputs/d7.txt");
                                        comc.load_from_file("inputs/d7.txt");
                                        comd.load_from_file("inputs/d7.txt");
                                        come.load_from_file("inputs/d7.txt");
                                        bool loadNiki = false; // derNiklaas Values, because he asked. (That dude -> https://github.com/derNiklaas/Advent-of-Code-2019)
                                        if (loadNiki) {
                                            std::vector<int64_t> code{3,8,1001,8,10,8,105,1,0,0,21,34,51,64,73,98,179,260,341,422,99999,3,9,102,4,9,9,1001,9,4,9,4,9,99,3,9,1001,9,4,9,1002,9,3,9,1001,9,5,9,4,9,99,3,9,101,5,9,9,102,5,9,9,4,9,99,3,9,101,5,9,9,4,9,99,3,9,1002,9,5,9,1001,9,3,9,102,2,9,9,101,5,9,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,99};
                                            coma.load_memory(code);
                                            comb.load_memory(code);
                                            comc.load_memory(code);
                                            comd.load_memory(code);
                                            come.load_memory(code);
                                        }

                                        nextInput = a;
                                        lastOutput = 0;
                                        coma.execute();
                                        nextInput = b;
                                        comb.execute();
                                        nextInput = c;
                                        comc.execute();
                                        nextInput = d;
                                        comd.execute();
                                        nextInput = e;
                                        come.execute();
                                        int running = 1;
                                        while(running) {
                                            coma.execute();
                                            comb.execute();
                                            comc.execute();
                                            comd.execute();
                                            running = come.execute();
                                        }
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
    // Maybe:     21596786 P.S: Yes!
}