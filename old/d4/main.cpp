#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> getDigits(int x) {
    std::vector<int> digits;
    for (int e = 10; e < 10'000'000; e*=10) {
        digits.push_back((x % e)/(e/10));
    }
    return digits;
}

int main() {
    int low = 145852;
    int high = 616942;

    /**
     * 111111
     * 111112
     * 111113
     * 111114
     * ...
     * 111119
     * 111120 falsch
     * 111121 falsch
     * 111122 true 
     */

    std::vector<int> possible_pw;
    std::vector<int> filtered_pw;
    for (int x = low; x < high; ++x) {
        std::vector<int> digits = getDigits(x);

        bool is_increasing = true;
        bool has_double = false;
        for (int i = digits.size() -1; i > 0; --i) {
            if (digits[i] == digits[i-1]) {
                has_double = true;
            }
                
            if (digits[i] > digits[i-1]) {
                is_increasing = false;
                break;
            }
        }

        if (is_increasing && has_double) {
            possible_pw.push_back(x);
        }
    }



    for (int x : possible_pw) {
        std::cout << x << ", ";
        bool has_double = false;

        std::vector<int> digits = getDigits(x);

        for (int i = digits.size() -1 -1; i > 1; --i) {
            if (digits[i] == digits[i-1] && digits[i] != digits[i+1] && digits[i] != digits[i-2])
                has_double = true;
            if (i == 2) {
                if (digits[0] == digits[1] && digits[0] != digits[2])
                    has_double = true; 
            }
            if (i == digits.size() -1 -1) {
                if (digits[digits.size()-1] == digits[digits.size()-2] && digits[digits.size()-1] != digits[digits.size()-3]) {
                    has_double = true;
                }
            }
        }

        if (has_double) {
            std::cout << "true\n";
            filtered_pw.push_back(x);
        } else {
            std::cout << "\n";
        }
    }
    // Wrong: 739, 1010
    std::cout << "Found " << possible_pw.size() << " possible passwords!\n";
    std::cout << "After filtering, there are just " << filtered_pw.size() << " possible passwords left!\n";

    // for (int i = low; i < high; ++i) {
    //     std::vector<int> digits;
    //     for (int e = 10; e < 10'000'000; e*=10) {
    //         digits.push_back(i % e);
    //     }
    // }
}