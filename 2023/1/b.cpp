#include <string>
#include <iostream>
using namespace std;

const string NUMBERS = "1234567890";
const string STRINGS[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int main() {
    string line;
    int sum = 0;

    while (getline(cin, line)) {
        string number = "";
        for (int i = 0; i < line.size(); i++) {
            string numToAdd = "";

            if (NUMBERS.find(line[i]) != string::npos) {
                numToAdd = line[i];
            } else {
                string sub = { line[i] };
                for (int j = i + 1; j < line.size(); j++) {
                    if (NUMBERS.find(line[i]) != string::npos) {
                        break;
                    }
                    sub += line[j];
                    int k = 1;
                    for (string num : STRINGS) {
                        if (sub == num) {
                            numToAdd = to_string(k);
                            break;
                        }
                        k++;
                    }
                    if (numToAdd != "") break;
                }
            }

            if (numToAdd == "") continue;

            if (number.size() <= 1) {
                number += numToAdd;
            } else {
                number[1] = numToAdd[0];
            }
        }

        if (number.size() == 1) {
            number += number;
        }
        sum += stoi(number);
    }
    cout << sum << endl;
}
