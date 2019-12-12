#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <inttypes.h>

class Moon {
public:
    std::array<int64_t, 3> pos_;
    std::array<int64_t, 3> init_pos_;
    std::array<int64_t, 3> vel_;

    std::array<int, 3> period;

    Moon(int x, int y, int z) {
        pos_[0] = x;
        pos_[1] = y;
        pos_[2] = z;

        init_pos_[0] = x;
        init_pos_[1] = y;
        init_pos_[2] = z;

        period[0] = 0;
        period[1] = 0;
        period[2] = 0;


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

    void gravity1D(std::vector<Moon*>& moons, int axis) {
        for (auto moon : moons) {
            int dx = moon->pos_[axis] - pos_[axis];
            if (dx >= 1) dx = 1;
            else if (dx <= -1) dx = -1;
            else dx = 0;

            vel_[axis] += dx;
        }
    }

    void velocity1D(int axis) {
        pos_[axis] += vel_[axis];
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

    bool is_initial(int axis, int index) {
        if (vel_[axis] == 0) {
            if (pos_[axis] == init_pos_[axis]) {
                period[axis] = index;
                return true;
            }
        }
        return false;
    }

    bool done(int axis) {
        return period[axis];
    }
};

int main() {
    {
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

        /**
         * <x=-1, y=0, z=2>
         * <x=2, y=-10, z=-7>
         * <x=4, y=-8, z=8>
         * <x=3, y=5, z=-1>
         */
        // std::vector<Moon*> moons {
        //     new Moon(-1, 0, 2),
        //     new Moon(2, -10, -7),
        //     new Moon(4, -8, 8),
        //     new Moon(3, 5, -1)
        // };

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

    for (int a = 0; a < 3; ++a) {
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

        /**
         * <x=-1, y=0, z=2>
         * <x=2, y=-10, z=-7>
         * <x=4, y=-8, z=8>
         * <x=3, y=5, z=-1>
         * Solution: 2772
         */
        // std::vector<Moon*> moons {
        //     new Moon(-1, 0, 2),
        //     new Moon(2, -10, -7),
        //     new Moon(4, -8, 8),
        //     new Moon(3, 5, -1)
        // };

        /**
         * <x=-8, y=-10, z=0>
         * <x=5, y=5, z=10>
         * <x=2, y=-7, z=3>
         * <x=9, y=-8, z=-3>
         * Solution: 4686774924
         */
        // std::vector<Moon*> moons {
        //     new Moon(-8, -10, 0),
        //     new Moon(5, 5, 10),
        //     new Moon(2, -7, 3),
        //     new Moon(9, -8, -3)
        // };
        for (int i = 0;;) {
            for (auto moon: moons) {
                moon->gravity1D(moons, a);
            }
            for (auto moon: moons) {
                moon->velocity1D(a);
            }
            ++i;
            bool d = true;
            bool initial = true;
            for (int m = 0; m < moons.size(); ++m) {
                // if (!moons[m]->done(a)) 
                if (!moons[m]->is_initial(a, i)) {
                    initial = false;
                }
                if (!moons[m]->done(a)) {
                    d = false;
                }
            }
            if (d && initial) break;
        }
        std::cout << "Axis " << a << ": ";
        for (auto moon: moons) {
            std::cout << moon->period[a] << ", ";
        }
        std::cout << "\n";
        
    }
}

// Bruteforce cancelled at: 8923000000 after a few hours
//                     327636285682704