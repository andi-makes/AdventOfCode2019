#include <iostream>
#include <fstream>

int calcFuel(int weight) {
	return weight / 3 - 2;
}

int calcFuelForFuel(int fuel) {
	int a = calcFuel(fuel);
	if (a <= 0) return 0;
	return a + calcFuelForFuel(a);
}

int main() {
	std::cout << "Day 1" << std::endl;
	std::ifstream file("inputs/d1.txt");

	int a;
	long b = 0;
	long c = 0;
	while (file >> a) {
		// std::cout << a << "\n";
		b += calcFuel(a);
		c += calcFuelForFuel(calcFuel(a));
	}
	std::cout << "The result for part 1 is: " << b << "\n";
	std::cout << "The result for part 2 is: " << c + b << "\n";

	// std::cout << "Test for the recursive function: 100756: " << calcFuelForFuel(100756);
	return 0;
}
