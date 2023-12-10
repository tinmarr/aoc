#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <array>

uint sum = 0;
uint currNum = 1;
uint prevCurrNum = 1;
uint gearsCount = 0;

std::string line;
std::array<int, 140> prev2Numbers;
std::array<int, 140> prevNumbers;
std::array<int, 140> currNumbers;
std::array<int, 140> prev2Copy;
std::array<int, 140> prevCopy;
std::array<int, 140> currCopy;
std::array<bool, 140> prevSymbols = {};
std::array<bool, 140> currSymbols = {};

int acquireNumber(int start, std::array<int, 140>& arr) {
    int num = arr[start];
    arr[start] = -1;
    if (num == -1) return 1;
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


void checkGears() {
    if (prevCurrNum != currNum) gearsCount += 1;
    prevCurrNum = currNum;
}

int main() {
    std::fstream input("input.txt");

    prev2Numbers.fill(-1);
    prevNumbers.fill(-1);
    currNumbers.fill(-1);


    while (std::getline(input, line)) {
        for (uint x = 0; x < line.length(); x++) {
            char c = line[x];
            if (std::isdigit(c)) {
                currNumbers[x] = (int)(c - '0');
            } else if (c == '*') {
                currSymbols[x] = true;
            }
        }

        for (uint x = 0;x < line.length();x++) {
            if (prevSymbols[x]) {
                prev2Copy = prev2Numbers;
                prevCopy = prevNumbers;
                currCopy = currNumbers;

                currNum *= acquireNumber(x - 1, prev2Copy);
                checkGears();
                currNum *= acquireNumber(x, prev2Copy);
                checkGears();
                currNum *= acquireNumber(x + 1, prev2Copy);
                checkGears();

                currNum *= acquireNumber(x - 1, prevCopy);
                checkGears();
                currNum *= acquireNumber(x + 1, prevCopy);
                checkGears();

                currNum *= acquireNumber(x - 1, currCopy);
                checkGears();
                currNum *= acquireNumber(x, currCopy);
                checkGears();
                currNum *= acquireNumber(x + 1, currCopy);
                checkGears();

                if (gearsCount == 2) {
                    sum += currNum;
                }
                currNum = 1;
                prevCurrNum = 1;
                gearsCount = 0;
            }
        }

        prev2Numbers = prevNumbers;
        prevNumbers = currNumbers;
        prevSymbols = currSymbols;
        currNumbers.fill(-1);
        currSymbols.fill(false);
    }

    std::cout << sum << std::endl;
    input.close();
    return 0;
}
