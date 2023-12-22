#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long numWinningPress(long time, long record) {
    long p1 = 0;
    long p2 = time;

    while (p1 < time) {
        if (record < p1 * (time - p1)) {
            break;
        }
        p1++;
    }
    while (p2 > p1) {
        if (record < p2 * (time - p2)) {
            break;
        }
        p2--;
    }

    return p2 - p1 + 1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out <filename>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    size_t n = 0;
    char* line1 = NULL;
    getline(&line1, &n, file);
    n = 0;
    char* line2 = NULL;
    getline(&line2, &n, file);

    long num = numWinningPress(atol(line1), atol(line2));

    free(line1);
    free(line2);
    printf("%d\n", num);
    return 0;
}
