#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numWinningPress(int time, int record) {
    int p1 = 0;
    int p2 = time;

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

    int num = numWinningPress(atoi(line1), atoi(line2));

    while (1) {
        line1 = strchr(line1, ' ');
        line2 = strchr(line2, ' ');
        if (line1 == NULL || line2 == NULL) {
            break;
        }
        line1 = &line1[1];
        line2 = &line2[1];

        num *= numWinningPress(atoi(line1), atoi(line2));
    }

    free(line1);
    free(line2);
    printf("%d\n", num);
    return 0;
}
