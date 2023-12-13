#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>

int main() {
    // File reading
    FILE* file = fopen("input.txt", "r");
    size_t n;
    ssize_t read;

    // Solution related
    const int cardsCount = 201;
    int cards[201] = { [0 ... 200] = 1 };

    // Temp
    int winningNumbers[10] = { 0 };
    int currMatches = 0;
    int currGame = 0;
    int currNum = 0;
    int foundWinning = 0;

    // Flow
    while (1) {
        char* line = NULL;
        read = getline(&line, &n, file);
        if (read == -1) {
            free(line);
            break;
        }

        for (int i = 0; i < read; i++) {
            if (isdigit(line[i])) {
                currNum = currNum * 10 + (line[i] - '0');
            } else if (line[i] == ':') {
                currGame = currNum;
                currNum = 0;
            } else if (line[i] == '|') {
                foundWinning = -1;
            } else if (currNum != 0 && (line[i] == ' ' || line[i] == '\n')) {
                if (foundWinning >= 0) {
                    winningNumbers[foundWinning] = currNum;
                    foundWinning++;
                } else {
                    for (int wn = 0; wn < 10; wn++) {
                        if (winningNumbers[wn] == currNum) {
                            currMatches++;
                        }
                    }
                }
                currNum = 0;
            }
        }

        for (int i = 0; i < currMatches && i < cardsCount; i++) {
            cards[currGame + i] += cards[currGame - 1];
        }

        foundWinning = 0;
        currMatches = 0;
    }
    int sum = 0;
    for (int i = 0; i < cardsCount; i++) {
        sum += cards[i];
    }

    printf("%i\n", sum);
    return 0;
}
