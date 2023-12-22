#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

class NumPair {
public:
    long start;
    long end;
};


class Map {
public:
    long start;
    long range;
    long mapStart;
    bool inRange(long n) {
        return this->start < n && n < this->start + this->range;
    }
    long diff() {
        return start - mapStart;
    }
    long end() {
        return start + range;
    }
    long map(long n) {
        return n - this->diff();
    }
    NumPair map(NumPair n) {
        return { this->map(n.start), this->map(n.end) };
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
    std::vector<NumPair> nums;
    std::vector<std::vector<Map>> allMaps;
    std::vector<Map> temp;

    std::cout << "Reading file\n";

    while (!file.eof()) {
        std::getline(file, line);

        if (nums.size() == 0) {
            size_t s = line.find_first_of(" ");
            bool skip = false;
            int numsSeen = 0;
            for (int i = s + 1; i < line.length(); i++) {
                if (line[i] == ' ') {
                    skip = false;
                    continue;
                } else if (skip) {
                    continue;
                }

                if (numsSeen % 2) {
                    nums.back().end = nums.back().start + std::atol(&line[i]);
                } else {
                    nums.push_back({ std::atol(&line[i]), -1 });
                }
                skip = true;
                numsSeen++;
            }
        } else if (line.empty()) {
            if (temp.size() > 0) {
                allMaps.push_back(temp);
                temp.clear();
            }
        } else if (!line.empty() && line.back() != ':') {
            Map m;
            m.mapStart = std::atol(&line[0]);
            size_t nextNum = line.find(' ') + 1;
            m.start = std::atol(&line[nextNum]);
            nextNum = line.find(' ', nextNum) + 1;
            m.range = std::atol(&line[nextNum]);
            temp.push_back(m);
        }
    }
    std::cout << "Processing maps...\n";

    std::vector<NumPair> newNums;
    for (std::vector<Map> maps : allMaps) {
        newNums.clear();
        for (int i = 0; i < nums.size(); i++) {
            bool mapFound = false;
            for (Map map : maps) {
                long o_start = std::max(map.start, nums[i].start);
                long o_end = std::min(map.end(), nums[i].end);

                if (o_start < o_end) {
                    newNums.push_back(map.map({ o_start, o_end }));
                    if (o_start > nums[i].start) {
                        nums.push_back({ nums[i].start, o_start });
                    }
                    if (nums[i].end > o_end) {
                        nums.push_back({ o_end, nums[i].end });
                    }
                    mapFound = true;
                    break;
                }
            }
            if (!mapFound) {
                newNums.push_back(nums[i]);
            }
        }
        nums = newNums;
    }

    long min = __LONG_MAX__;
    for (NumPair n : nums) {
        if (n.start < min) min = n.start;
    }

    file.close();
    std::cout << min << std::endl;

    return 0;
}
