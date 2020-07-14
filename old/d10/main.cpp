#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
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

Asteroid* base;

bool compare(Asteroid* a1, Asteroid* a2) {
    double dist1 = std::sqrt(std::pow(a1->x_ - base->x_, 2) + std::pow(a1->y_ - base->y_, 2));
    double dist2 = std::sqrt(std::pow(a1->x_ - base->x_, 2) + std::pow(a1->y_ - base->y_, 2));
    return dist2 < dist1;
}   

int main() {
    {
        std::cout << "Day 10, Part 1\n" << 
            "There wont be a part 2 solution of this day, that would be kinda crazy with this kind of setup.\n";

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
                base = a;
            }
        }
        std::cout << asteroids.size() << ", " << x << ", " << y << "\n";
        std::cout << "Number of asteroids in sight: " << max_asteroids << "\n";
    }

    {
        std::ifstream input("inputs/d10.txt");
        std::map<double, std::vector<Asteroid*>> asteroids;

        std::string line;
        while(std::getline(input, line)) {
            static int y = 0;
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] == '#') {
                    auto a = new Asteroid(i, y);
                    double angle = std::atan2(double(a->y_ - base->y_), double(a->x_ - base->x_));
                    angle = angle <= 0 ? abs(angle) : 2 * M_PI - angle;
                    asteroids[angle].push_back(a);
                }
            }
            ++y;
        }

        

        for (auto a: asteroids) {
            std::sort(a.second.begin(), a.second.end(), compare);
        }

        std::vector<Asteroid*> dest;
        for (int d = 0; d < 200;) {
            for (auto a: asteroids) {
                if (a.second.size() > 0) {
                    int index;
                    double dist = 1000;
                    for (int i = 0; i < a.second.size(); ++i) {
                        double tmp = std::sqrt(std::pow(a.second[i]->x_ - base->x_, 2) + std::pow(a.second[i]->y_ - base->y_, 2));
                        if (tmp < dist) {
                            dist = tmp;
                            index = i;
                        }
                    }


                    std::cout << "[" << d << "] PEW: (" << a.second.back()->x_ << "|" << a.second.back()->y_ << ")\n";
                    dest.push_back(a.second[index]);
                    a.second.erase(a.second.begin() + index);
                    ++d;
                }
            }
        }
        
    } // Lösung: 502
}

// Wrong: 210, 36, 206