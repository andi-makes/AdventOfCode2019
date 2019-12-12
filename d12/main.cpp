#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <inttypes.h>

class Moon {
public:
    std::array<int, 3> pos_;
    std::array<int, 3> vel_;

    Moon(int x, int y, int z) {
        pos_[0] = x;
        pos_[1] = y;
        pos_[2] = z;

        vel_[0] = 0;
        vel_[1] = 0;
        vel_[2] = 0;
    }

    void gravity(std::vector<Moon*>& moons) {
        for (auto moon : moons) {
            int dx = moon->pos_[0] - pos_[0];
            int dy = moon->pos_[1] - pos_[1];
            int dz = moon->pos_[2] - pos_[2];
            if (dx >= 1) dx = 1;
            else if (dx <= -1) dx = -1;
            else dx = 0;

            if (dy >= 1) dy = 1;
            else if (dy <= -1) dy = -1;
            else dy = 0;

            if (dz >= 1) dz = 1;
            else if (dz <= -1) dz = -1;
            else dz = 0;

            vel_[0] += dx;
            vel_[1] += dy;
            vel_[2] += dz;
        }
    }

    void velocity() {
         pos_[0] += vel_[0];
         pos_[1] += vel_[1];
         pos_[2] += vel_[2];
    }

    /**
     * THIS IS NOT ENERGY 👿👿👿
     * Des is a verdammter deppater pfusch bis zum geht nimma!
     * Da güt nedamoi der Energieerhaltungssatz! 👿👿👿
     */
    int energy() {
        return (std::abs(pos_[0]) + std::abs(pos_[1]) + std::abs(pos_[2])) * (std::abs(vel_[0]) + std::abs(vel_[1]) + std::abs(vel_[2]));
    }
};

int main() {
    /**
     * <x=14, y=4, z=5>
     * <x=12, y=10, z=8>
     * <x=1, y=7, z=-10>
     * <x=16, y=-5, z=3>
     */
    std::vector<Moon*> moons {
        new Moon(14, 4, 5),
        new Moon(12, 10, 8),
        new Moon(1, 7, -10),
        new Moon(16, -5, 3)
    };

    for (int i = 0; i <= 1000; ++i) {
        int energy_sum = 0;
        std::cout << "Step " << i << "\n";
        for (auto moon: moons) {
            std::cout << "Pos: (" << moon->pos_[0] << "|" << moon->pos_[1] << "|" << moon->pos_[2] << "), ";
            std::cout << "Vel: (" << moon->vel_[0] << "|" << moon->vel_[1] << "|" << moon->vel_[2] << "),";
            std::cout << "\"Energy\": " << moon->energy() << "\n";
            energy_sum += moon->energy();
        }
        std::cout << "Total \"Energy\": " << energy_sum << "\n";
        for (auto moon: moons) {
            moon->gravity(moons);
        }
        for (auto moon: moons) {
            moon->velocity();
        }
    }
}