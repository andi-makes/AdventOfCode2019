#include <computer/Computer.h>
#include <computer/Instructionset.h>
#include <ncurses.h>

#include <array>

#include <chrono>
#include <thread>

int ball_pos = 16;
int ball_dir = 0;
int paddle_pos = 0;

int64_t IN_ISR() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    mvprintw(1, 50, "                ");
    mvprintw(2, 50, "                ");
    mvprintw(3, 50, "                ");

    mvprintw(1, 50, "%2d", ball_dir);
    mvprintw(2, 50, "%d", ball_pos);
    mvprintw(3, 50, "%d", paddle_pos);
    refresh();
    // getch();
    int e = ball_pos - paddle_pos;
    if (e > 0) return 1;
    if (e < 0) return -1;
    return 0;
}

// int blocks = 0;

void OUT_ISR(int64_t a) {
    static std::array<int, 3> buf;
    static int i = 0;

    std::this_thread::sleep_for(std::chrono::nanoseconds(10));

    buf[i] = a;

    ++i;

    if (i >= 3) {
        i = 0;
        // std::cout << buf[0] << ", " << buf[1] << ", " << buf[2] << "\n";
        if (buf[0] == -1 && buf[1] == 0) {
            mvprintw(0, 50, "                ");
            mvprintw(0, 50, "%d", buf[2]);
            return;
        }
        switch(buf[2]) {
            case 0: // Air
                mvprintw(buf[1], buf[0], " ");
                break;
            case 3: // Paddle Tile
                paddle_pos = buf[0];
            case 1: // Wall tile
            case 2: // Block tile
                mvprintw(buf[1], buf[0], "X");
                break;
            case 4: // Ball
                mvprintw(buf[1], buf[0], "O");
                ball_dir = ball_pos - buf[0];
                ball_pos = buf[0];
                break;
        }
        refresh();
    }
}

int main() {
    inISR = IN_ISR;
    outISR = OUT_ISR;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    enableISR = true;

    InstructionSet iss;
    iss.enable_all();
    Computer com;
    com.load_from_file("inputs/d13.txt");
    com.alter_memory(2, 0); // HAXXOR
    iss.execute(com);

    getch();
    endwin();

    // std::cout << "Blocks: " << blocks << "\n";
}
// Too High: 5365