#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <string>
#include <sstream>

class SpaceObject {
public:
    SpaceObject* orbits_around_;
    std::string id_;

    SpaceObject(SpaceObject* orbits_around, std::string id) {
        orbits_around_ = orbits_around;
        id_ = id;
    }

    void assign_orbit(SpaceObject* orbits_around) {
        orbits_around_ = orbits_around;
    }

    int number_of_orbits() {
        if (orbits_around_ != nullptr) {
            return orbits_around_->number_of_orbits() + 1;
        } else {
            return 0;
        }
    }

    SpaceObject* go_up(int i) {
        if (i == 0 || orbits_around_ == nullptr) {
            return this;
        } else {
            return orbits_around_->go_up(i-1);
        }
    }
};

int main() {
    std::cout << "Day 6 - Part 1\n";
    std::map<std::string, SpaceObject*> space_map;

    std::vector<std::string> input;
    {
        std::fstream inputfile("inputs/d6.txt");
        std::string tmp;
        while (std::getline(inputfile, tmp, '\n')) {
            input.push_back(tmp);
        }
    }

    std::vector<std::string> id;
    for (std::string line: input) {
        std::stringstream line_stream(line);
        std::string first;
        std::string second;
        std::getline(line_stream, first, ')');
        std::getline(line_stream, second, ')');

        std::cout << first << " | " << second << "\n";
        if (!(space_map.find(first) != space_map.end())) {
            space_map.insert(std::make_pair(first, new SpaceObject(nullptr, first)));
            id.push_back(first);
        }
        if (!(space_map.find(second) != space_map.end())) {
            space_map.insert(std::make_pair(second, new SpaceObject(nullptr, second)));
            id.push_back(second);
        }
        space_map[second]->assign_orbit(space_map[first]);
    }

    int number_of_orbits = 0;
    for (std::string x: id) {
        number_of_orbits += space_map[x]->number_of_orbits();
    }
    std::cout << number_of_orbits << "\n";

    std::cout << "Part 2\n";
    bool found_cross_point = false;
    SpaceObject* santa = space_map["SAN"];
    SpaceObject* me    = space_map["YOU"];
    int x = 1;
    int y = 1;
    
    std::cout << me->go_up(2)->id_ << " should be J" << "\n";

    for (x = 1; x < me->number_of_orbits(); ++x) {
        for (y = 1; y < santa->number_of_orbits(); ++y) {
            std::string mestr, santastr;
            mestr = me->go_up(x)->id_;
            santastr = santa->go_up(y)->id_;
            // std::cout << mestr << "==" << santastr << ", " << x-1 << ", " << y-1 <<"\n";
            if (mestr == santastr) {
                found_cross_point = true;
                x -= 1;
                y -= 1;
                break;
            }
        }
        if (found_cross_point) break;
    }
    std::cout << "x: " << x << ", y: " << y << ", d: " << x+y << "\n";
}