#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

int processLine(std::list<int> line, bool all0 = false) {
    if (all0) {
        return 0;
    }
    all0 = true;
    std::list<int> nextLine;
    int last;
    for (std::list<int>::iterator pI = line.begin(); pI != line.end(); pI++) {
        if (pI != line.begin()) {
            int val = *pI - last;
            all0 &= val == 0;
            nextLine.push_back(val);
        }
        last = *pI;
    }
    return line.back() + processLine(nextLine, all0);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./a.out <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) return 1;

    std::string line;
    int sum = 0;
    while (1) {
        std::getline(file, line);
        if (file.eof()) break;

        std::list<int> nums;

        int i = 0;
        while (i < line.length()) {
            nums.push_back(std::stoi(&line[i]));
            i = line.find(' ', i + 1);
        }

        sum += processLine(nums);
    }

    std::cout << sum << "\n";
    return 0;
}
