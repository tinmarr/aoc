#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>


const int numRed = 12;
const int numGreen = 13;
const int numBlue = 14;

int main() {
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int sum = 0;

    while (1) {
        len = 0;
        read = getline(&line, &len, stdin);
        if (read == -1) {
            break;
        }
        int game = 0;
        int gameFound = 0;
        int possible = 1;
        int space = 0;
        int prevNum = 0;
        int maxRed = 0;
        int maxBlue = 0;
        int maxGreen = 0;
        int i = 0;

        while (1) {
            char c = line[i];
            if (c == 0) { break; }
            if (isdigit(c) && gameFound) {
                prevNum *= 10;
                prevNum += c - '0';
            } else if (c == ':') {
                gameFound = 1;
            } else if (c == ' ') {
                space = 1;
            } else {
                if (c == 'b') {
                    if (prevNum > maxBlue) { maxBlue = prevNum; }
                } else if (c == 'r') {
                    if (prevNum > maxRed) { maxRed = prevNum; }
                } else if (c == 'g') {
                    if (prevNum > maxGreen) { maxGreen = prevNum; }
                }
                space = 0;
                prevNum = 0;
            }
            i++;
        }
        sum += maxBlue * maxGreen * maxRed;
    }
    printf("%i\n", sum);
    free(line);
}
