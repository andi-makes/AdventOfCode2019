#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

class Asteroid {
public:
    int x_, y_;

    Asteroid(int x, int y) : x_(x), y_(y) {}

    int asteroids_in_sight(const std::vector<Asteroid*>& asteroids) {
        std::vector<double> angles;
        int in_sight = 0;
        for (Asteroid* a : asteroids) {
            // if (a->x_ != x_ && a->y_ != y_) {
                double angle = std::atan2(double(a->y_ - y_), double(a->x_ - x_));

                if (std::find(angles.begin(), angles.end(), angle) == angles.end()) {
                    angles.push_back(angle);
                    ++in_sight;
                }
            // }
        }

        return in_sight;
    }
};

int main() {
    std::ifstream input("inputs/d10.txt");
    std::vector<Asteroid*> asteroids;

    std::string line;
    while(std::getline(input, line)) {
        static int y = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == '#') {
                asteroids.push_back(new Asteroid(i, y));
            }
        }
        ++y;
    }

    int max_asteroids = 0;
    int x, y;
    for (Asteroid* a : asteroids) {
        int ast_count = a->asteroids_in_sight(asteroids);
        if (ast_count > max_asteroids) {
            max_asteroids = ast_count;
            x = a->x_;
            y = a->y_;
        }
    }
    std::cout << asteroids.size() << ", " << x << ", " << y << "\n";
    std::cout << "Number of asteroids in sight: " << max_asteroids << "\n";
}

// Wrong: 210, 36, 206