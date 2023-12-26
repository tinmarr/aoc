#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Hand {
   public:
    std::array<int, 5> hand;
    int bet;
    int type;

    Hand(std::string hand, int bet) {
        this->bet = bet;
        this->type = -1;

        u_int8_t type[13] = {};
        u_int8_t pair = 0;
        u_int8_t three = 0;
        for (int i = 0; i < 5; i++) {
            char c = hand[i];
            u_int8_t changed;
            switch (c) {
                case 'A':
                    changed = 12;
                    break;
                case 'K':
                    changed = 11;
                    break;
                case 'Q':
                    changed = 10;
                    break;
                case 'J':
                    changed = 9;
                    break;
                case 'T':
                    changed = 8;
                    break;
                default:
                    changed = atoi(&c) - 2;
            }
            this->hand[i] = changed + 2;
            type[changed]++;
            switch (type[changed]) {
                case 2:
                    pair++;
                    break;
                case 3:
                    pair--;
                    three++;
                    break;
                case 4:
                    this->type = 5;
                    break;
                case 5:
                    this->type = 6;
                    break;
            }
        }
        if (this->type < 0) {
            if (pair == 2) {
                this->type = 2;
            } else if (three == 1) {
                if (pair == 1) {
                    this->type = 4;
                } else {
                    this->type = 3;
                }
            } else if (pair == 1) {
                this->type = 1;
            } else {
                this->type = 0;
            }
        }
        if (this->type == -1) {
            std::cout << "Hand type still -1 for hand " << hand << "\n";
        }
    }

    bool operator<(Hand &other) {
        if (type != other.type) {
            return type < other.type;
        }
        for (int i = 0; i < 5; i++) {
            if (hand[i] != other.hand[i]) {
                return hand[i] < other.hand[i];
            }
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./a.out <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Could not open provided file\n";
        return 1;
    }

    std::vector<Hand> hands;
    std::string line;
    std::getline(file, line);
    while (!file.eof()) {
        hands.push_back({line.substr(0, 5), std::stoi(line.substr(6))});
        std::getline(file, line);
    }

    std::sort(hands.begin(), hands.end());
    long sum = 0;

    for (int i = 0; i < hands.size(); i++) {
        sum += hands[i].bet * (i + 1);
    }

    std::cout << sum << "\n";
    return 0;
}
