#include <computer/Computer.h>
#include <computer/Instructionset.h>

#include <vector>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Tile {
public:
    int color;
    bool has_been_painted;

    Tile(): color(0), has_been_painted(false) {}

    void paint(int c) {
        color = c;
        if (c == 1) has_been_painted = true;
    }
};

Tile map[100][100];
int robot_dir = UP;

int x = 50;
int y = 50;

int64_t IN_ISR() {
    return map[y][x].color;
}

void OUT_ISR(int64_t a) {
    static int i = 0;
    if (i == 0)  {
        map[y][x].paint(a);
    }
    else if (i == 1) {
        if (a == 0) {
            switch(robot_dir) {
                case UP: robot_dir = LEFT; x -= 1; break;
                case LEFT: robot_dir = DOWN; y -= 1; break;
                case DOWN: robot_dir = RIGHT; x += 1; break;
                case RIGHT: robot_dir = UP; y += 1; break;
            }
        } else if (a == 1) {

            switch(robot_dir) {
                case UP: robot_dir = RIGHT; x += 1; break;
                case RIGHT: robot_dir = DOWN; y -= 1; break;
                case DOWN: robot_dir = LEFT; x -= 1; break;
                case LEFT: robot_dir = UP; y += 1; break;
            }
        }
    }
    ++i;
    if (i >= 2) i = 0;
}

int main() {
    inISR = IN_ISR;
    outISR = OUT_ISR;

    enableISR = true;

    map[y][x].paint(1);

    InstructionSet iss;
    iss.enable_all();
    Computer com;
    com.load_from_file("inputs/d11.txt");
    iss.execute(com);

    int white_tiles = 0;
    for (int y = 0; y < 100; ++y) {
        std::cout << "|";
        for (int x = 0; x < 100; ++x) {
            if (map[99-y][x].color == 1) std::cout << "X";
            else std::cout << " ";
            if (map[y][x].has_been_painted) ++white_tiles;
        }
        std::cout << "|\n";
    }

    std::cout << white_tiles << "\n";
}
// Too High: 5365