#include <computer/Computer.h>
#include <computer/Instructionset.h>
#include <ncurses.h>

#include <array>

int64_t IN_ISR() {
    
}

int blocks = 0;

void OUT_ISR(int64_t a) {
    static std::array<int, 3> buf;
    static int i = 0;
    buf[i] = a;

    ++i;

    if (i >= 3) {
        i = 0;
        std::cout << buf[0] << ", " << buf[1] << ", " << buf[2] << "\n";

        switch(buf[2]) {
            case 2: // Block tile
                ++blocks;
                break;
        }
    }
}

int main() {
    inISR = IN_ISR;
    outISR = OUT_ISR;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    enableISR = true;

    InstructionSet iss;
    iss.enable_all();
    Computer com;
    com.load_from_file("inputs/d13.txt");
    iss.execute(com);

    std::cout << "Blocks: " << blocks << "\n";
}
// Too High: 5365