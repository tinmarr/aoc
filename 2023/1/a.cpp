#include <string>
#include <iostream>
using namespace std;

const string NUMBERS = "1234567890";

int main() {
    string line;
    int sum = 0;

    while (getline(cin, line)) {
        string number = "";
        for (int i = 0; i < line.size(); i++) {
            if (NUMBERS.find(line[i]) != string::npos) {
                if (number.size() <= 1) {
                    number += line[i];
                } else {
                    number[1] = line[i];
                }
            }
        }
        if (number.size() == 1) {
            number += number;
        }
        sum += stoi(number);
    }
    cout << sum << endl;
}
