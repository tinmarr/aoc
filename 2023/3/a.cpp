#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <array>


int acquireNumber(int start, std::array<int, 140>& arr) {
    int num = arr[start];
    arr[start] = -1;
    if (num == -1) return 0;
    // Numbers to the left
    int8_t i = 1;
    while (start >= i && arr[start - i] != -1) {
        num += arr[start - i] * std::pow(10, i);
        arr[start - i] = -1;
        i++;
    }
    // Numbers to the right
    i = 1;
    while (start + i < arr.size() && arr[start + i] != -1) {
        num *= 10;
        num += arr[start + i];
        arr[start + i] = -1;
        i++;
    }

    return num;
}

int main() {
    std::fstream input("input.txt");
    uint sum = 0;

    std::string line;
    std::array<int, 140> prevNumbers;
    std::array<bool, 140> prevSymbols = {};
    std::array<int, 140> currNumbers;
    std::array<bool, 140> currSymbols = {};

    prevNumbers.fill(-1);
    currNumbers.fill(-1);

    while (std::getline(input, line)) {
        for (uint x = 0; x < line.length(); x++) {
            char c = line[x];
            if (std::isdigit(c)) {
                currNumbers[x] = (int)(c - '0');
            } else if (c != '.') {
                currSymbols[x] = true;
            }
        }

        for (uint x = 0;x < line.length();x++) {
            if (currSymbols[x]) {
                sum += acquireNumber(x - 1, currNumbers);
                sum += acquireNumber(x + 1, currNumbers);
                sum += acquireNumber(x - 1, prevNumbers);
                sum += acquireNumber(x, prevNumbers);
                sum += acquireNumber(x + 1, prevNumbers);
            }
            if (prevSymbols[x]) {
                sum += acquireNumber(x - 1, currNumbers);
                sum += acquireNumber(x, currNumbers);
                sum += acquireNumber(x + 1, currNumbers);
            }
        }

        prevNumbers = currNumbers;
        prevSymbols = currSymbols;
        currNumbers.fill(-1);
        currSymbols.fill(false);
    }

    std::cout << sum << std::endl;
    input.close();
}
