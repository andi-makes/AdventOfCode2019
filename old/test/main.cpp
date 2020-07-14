#include <ncurses.h>
#include <string>

class Box {
private:
    WINDOW *win_;
    int x_, y_, width_, height_;
public:
    Box(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {
        win_ = newwin(height_, width_, y, x);
        box(win_,0,0);
        wrefresh(win_);
    }
};

int main() {
    WINDOW *foot_win;
    WINDOW *header_win;
    WINDOW *body_win;
    int startx, starty, width, height;
    int ch;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    height = 3;
    width = 10;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;
    refresh();

    header_win = newwin(3, COLS/2-2, 0,0);
    box(header_win,0,0);
    mvwprintw(header_win, 1, 1, "Intcode Computer");
    wrefresh(header_win);

    body_win = newwin(LINES - 6, COLS/2-2, 3, 0);
    box(body_win,0,0);
    mvwprintw(body_win, 1, 1, "load [filename] -- Loads the memory of that file");
    wrefresh(body_win);

    foot_win = newwin(3, COLS/2-2, LINES-3, 0);
    box(foot_win, 0, 0);
    mvwprintw(foot_win, 1, 1, "$ ");
    wrefresh(foot_win);
    while (true) {
        static std::string command = "";
        char ch = getch();
        if (ch == '\n') {
            if (command.find("load") != std::string::npos) {
                wprintw(body_win, "NICE LOAD MATE");
                wrefresh(body_win);
            } else if (command.find("exit") != std::string::npos) {
                break;
            }
            command = "";

            wclear(foot_win);
            box(foot_win, 0, 0);
            mvwprintw(foot_win, 1, 1, "$ ");
            wrefresh(foot_win);
        } else {
            command += ch;
            waddch(foot_win, ch);
            wrefresh(foot_win);
        }
    }
    endwin();    
    return 0;
}