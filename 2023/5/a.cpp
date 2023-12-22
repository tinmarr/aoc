#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

class Map {
public:
    long start;
    long range;
    long mapStart;
    bool inRange(long n) {
        return this->start < n && n < this->start + this->range;
    }
    long map(long n) {
        int diff = n - this->start;
        return this->mapStart + diff;
    }

};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./a.out <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) { std::cout << "Could not open file " << argv[1] << std::endl; return 1; }

    std::string line;
    std::vector<long> nums;
    std::vector<Map> maps;

    while (!file.eof()) {
        std::getline(file, line);

        if (nums.size() == 0) {
            size_t s = line.find_first_of(" ");
            bool skip = false;
            for (int i = s + 1; i < line.length(); i++) {
                if (line[i] == ' ') {
                    skip = false;
                    continue;
                } else if (skip) {
                    continue;
                }

                nums.push_back(std::atol(&line[i]));
                skip = true;
            }
        } else if (line.empty()) {
            if (maps.size() > 0) {
                for (int i = 0; i < nums.size(); i++) {
                    for (Map map : maps) {
                        if (map.inRange(nums[i])) {
                            nums[i] = map.map(nums[i]);
                            break;
                        }
                    }
                }
                maps.clear();
            }
        } else if (line.back() != ':') {
            // build maps
            Map m;
            m.mapStart = std::atol(&line[0]);
            size_t nextNum = line.find(' ') + 1;
            m.start = std::atol(&line[nextNum]);
            nextNum = line.find(' ', nextNum) + 1;
            m.range = std::atol(&line[nextNum]);
            maps.push_back(m);
        }
    }
    file.close();

    std::sort(nums.begin(), nums.end());
    std::cout << nums[0] << std::endl;

    return 0;
}
