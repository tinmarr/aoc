#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum Type { high, one, two, three, full, four, five, unassigned = -1 };
const u_int8_t jack = 9;

class Hand {
   public:
    std::array<int, 5> hand;
    int bet;
    Type type;

    Hand(std::string hand, int bet) {
        this->bet = bet;
        this->type = unassigned;

        u_int8_t typeCounter[13] = {0};
        u_int8_t pair = 0;
        u_int8_t nthree = 0;
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
            typeCounter[changed]++;
            if (changed == jack) {
                this->hand[i] = 0;
            } else {
                this->hand[i] = changed + 2;
                switch (typeCounter[changed]) {
                    case 2:
                        pair++;
                        break;
                    case 3:
                        pair--;
                        nthree++;
                        break;
                    case 4:
                        this->type = four;
                        break;
                    case 5:
                        this->type = five;
                        break;
                }
            }
        }

        if ((this->type == four && typeCounter[jack]) || typeCounter[jack] >= 4) {
            this->type = five;
        } else if (this->type == unassigned) {
            if (pair == 1) {
                switch (typeCounter[jack]) {
                    case 0:
                        if (nthree == 1) {
                            this->type = full;
                        } else {
                            this->type = one;
                        }
                        break;
                    case 1:
                        this->type = three;
                        break;
                    case 2:
                        this->type = four;
                        break;
                    case 3:
                        this->type = five;
                        break;
                }
            } else if (nthree == 1) {
                switch (typeCounter[jack]) {
                    case 0:
                        this->type = three;
                        break;
                    case 1:
                        this->type = four;
                        break;
                    case 2:
                        this->type = five;
                        break;
                }
            } else if (pair == 2) {
                switch (typeCounter[jack]) {
                    case 0:
                        this->type = two;
                        break;
                    case 1:
                        this->type = full;
                        break;
                }
            } else {
                switch (typeCounter[jack]) {
                    case 0:
                        this->type = high;
                        break;
                    case 1:
                        this->type = one;
                        break;
                    case 2:
                        this->type = three;
                        break;
                    case 3:
                        this->type = four;
                        break;
                }
            }
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
        Hand hand{line.substr(0, 5), std::stoi(line.substr(6))};
        hands.push_back(hand);
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
