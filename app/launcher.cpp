#include "day1.h"

#include <iostream>

int main() {
	std::cout << "Hello World!" << std::endl;

	int day;
	std::cin >> day;

	switch (day) {
	case 1: {
		int total_mass	 = 0;
		int total_mass_2 = 0;
		for (auto mass : day1::masses) {
			total_mass += day1::fuel_per_module(mass);
			total_mass_2 += day1::fuel_per_module_part_2(mass);
		}
		std::cout << "Day 1 Part 1: Total mass needed: " << total_mass << "!" << std::endl;
		std::cout << "Day 1 Part 2: Total mass needed: " << total_mass_2 << "!" << std::endl;

	} break;
	default: std::cout << "Couldn't find that day, sorry." << std::endl;
	}

	return 0;
}