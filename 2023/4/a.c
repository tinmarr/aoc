#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>

int main() {
    // File reading
    FILE* file = fopen("input.txt", "r");
    char* line;
    size_t n;
    ssize_t read;

    // Solution related
    int winningNumbers[10] = { 0 };
    int sum = 0;

    // Temp
    int i;
    int currentPoints = 0;
    int currNum = 0;
    int foundWinning = 0;

    // Flow
    while (1) {
        read = getline(&line, &n, file);
        if (read == -1) {
            break;
        }

        i = 0;
        while (1) {
            if (isdigit(line[i])) {
                currNum = currNum * 10 + (line[i] - '0');
            } else if (line[i] == ':') {
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
                            if (currentPoints == 0) {
                                currentPoints = 1;
                            } else {
                                currentPoints *= 2;
                            }
                            break;
                        }
                    }
                }
                currNum = 0;

                if (line[i] == '\n') {
                    break;
                }
            }
            i++;
        }

        sum += currentPoints;
        currentPoints = 0;
        foundWinning = 0;
    }

    printf("%i\n", sum);
    return 0;
}
