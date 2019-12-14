#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

class Ingredient {
public: 
    std::string id_;
    long quantity_;
    long result_quantity_;
    std::map<std::string, int> ingredients_;

    Ingredient(std::string id, std::map<std::string, int> ingredients, int result_quantity): 
        id_(id), ingredients_(ingredients), quantity_(0), result_quantity_(result_quantity) {}

    void order(int quantity, std::map<std::string, Ingredient*>& store) {
        if (id_ == "ORE") {
            quantity_ += quantity;
            return;
        }
        if (quantity_ >= quantity) {
            if (!(id_ == "FUEL")) quantity_ -= quantity;
            return;
        } else {
            while(quantity > quantity_) {
                for (auto pair : ingredients_) {
                    store[pair.first]->order(pair.second, store);
                }
                quantity_ += result_quantity_;
            }
            if (!(id_ == "FUEL")) quantity_ -= quantity;
        }
    }
};

std::map<std::string, Ingredient*> store;

int main() {
    std::ifstream input("inputs/d14.txt");

    {
        std::string line;
        while(std::getline(input, line)) {
            // std::cout << line << "\n";

            std::regex r("(.*) => (.*)");

            std::smatch match;
            std::regex_match(line, match, r);

            std::map<std::string, int> ingredients;

            {
                std::string s = match[1];
                std::regex r1("(\\d+) (\\w+)");

                std::sregex_iterator it(s.begin(), s.end(), r1);
                auto end_of_iterator = std::sregex_iterator();
                
                while(it != end_of_iterator) {
                    std::smatch m = *it;

                    std::cout << m.str(1) << "*" << m.str(2) << " + ";
                    ingredients.insert(std::make_pair(m.str(2), std::stoi(m.str(1))));
                    ++it;
                }
                std::cout << "== ";
            }

            {
                std::string s = match[2];
                std::regex r1("(\\d+) (\\w+)");

                std::smatch m;
                std::regex_match(s, m, r1);
                
                std::cout << m.str(1) << "* " << m.str(2) << "\n";
                store.insert(std::make_pair(m.str(2), new Ingredient(m.str(2), ingredients, std::stoi(m.str(1)))));
            }
        }
    }
    store.insert(std::make_pair("ORE", new Ingredient("ORE", {}, 1)));
    store["FUEL"]->order(1, store);

    std::cout << store["ORE"]->quantity_ << "\n";

    long ores = 1000000000000;
    long first_estimate = ores / store["ORE"]->quantity_;
    std::cout << first_estimate << "\n";
    store["FUEL"]->order(first_estimate-1, store);

    for (long i = first_estimate; store["ORE"]->quantity_ < ores; ++i) {
        store["FUEL"]->order(1, store);
        std::cout << i << "\n";
    }
    std::cout << store["FUEL"]->quantity_ << "\n";
}