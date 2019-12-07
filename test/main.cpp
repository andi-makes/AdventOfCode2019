#include "computer/Computer.h"
#include "computer/Instructionset.h"
#include <iostream>

#include <ncurses.h>

int main() {
    // InstructionSet instruction_set;
    // instruction_set.enable_all();
    // Computer com = Computer(instruction_set.get());

    // while (true) {
    //     static std::string command;
    //     std::cout << "$ (Note: It does nothing right now ;D)";
    //     std::getline(std::cin, command);
    //     std::cout << command;
    //     if (command.find("load")) {
    //         std::cout << "EYYY; found load :D \n";
    //     }
    // }

    initscr();
    printw("Hello Ncurses!");
    refresh();
    getch();
    endwin();
    return 0;

    
    // com.execute();
}