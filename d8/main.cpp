#include <iostream>
#include <fstream>
#include <array>

template<int width, int height>
class Layer {
private:
    std::array<std::array<int, width>, height> data;
public:
    Layer() {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                data[h][w] = 2;
            }
        }
    }

    void insert_into(int x, int y, int number) {
        data[y][x] = number - '0';
    } 

    void print() {
        std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                std::cout << data[h][w] << " ";
            }
            std::cout << "\n";
        }
        std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    void printFormat() {
        std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                char printme = ' ';
                if (data[h][w] == 1) {
                    printme = 'X';
                }
                std::cout << printme << " ";
            }
            std::cout << "\n";
        }
        std::cout<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    int pixel(int x, int y) {
        return data[y][x];
    }

    int number_of(int value) {
        int number_of_value = 0;
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                if (data[h][w] == value) {
                    ++number_of_value;
                }
            }
        }
        return number_of_value;
    }
};

int main() {
    std::fstream file("inputs/d8.txt");
    const int width = 25;
    const int height = 6;
    const int layersize = width * height;
    std::string data;
    std::getline(file, data);
    int datasize = data.size();
    int layercount = datasize / layersize;
    std::cout << data.size() << " / " << layersize << " = " << layercount << "\n";

    std::array<Layer<width, height>*, 100> layer; // 100 Layer, like calculated above

    for (int l = 0; l < layercount; ++l) {
        layer[l] = new Layer<width, height>();
        for (int h = 0; h < height; ++h){
            for (int w = 0; w < width; ++w) {
                layer[l]->insert_into(w, h, data[w + h * width + l * layersize]);
            }
        }
    }
    
    layer[2]->print();

    std::cout << "Lowest\n";

    int fewest_zeros = 100000;
    int result = 0;
    for (int i = 0; i < layer.size(); ++i) {
        if (layer[i]->number_of(0) < fewest_zeros) {
            layer[i]->print();
            std::cout << layer[i]->number_of(0) << "\n";
            fewest_zeros = layer[i]->number_of(0);
            result = layer[i]->number_of(1) * layer[i]->number_of(2);
        }
    }

    std::cout << "Your result for Part 1 is `" << result << "´!\n";
    // Too low: 1736

    Layer<width, height> message{};




    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            for (int l = 0; l < layer.size(); ++l) {
                if (layer[l]->pixel(w, h) != 2) {
                    message.insert_into(w, h, layer[l]->pixel(w, h) + '0');
                    break;
                }
            }
        }
    }
    message.printFormat();
}