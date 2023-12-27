#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct Node {
    int id;
    int type;
    int left;
    int right;
    Node* pLeft;
    Node* pRight;
} Node;

typedef long long longlong;

int compareNodes(const void* a, const void* b) {
    const Node* na = (const Node*)a;
    const Node* nb = (const Node*)b;

    if (na->id < nb->id) return -1;
    if (na->id > nb->id) return 1;
    return 0;
}

longlong gcd(longlong a, longlong b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, (a % b));
    }
}

longlong lcm(longlong a, longlong b) { return a * (b / gcd(a, b)); }

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Usage: ./b.out <filename>");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    size_t n = 0;
    char* actions = NULL;
    ssize_t numActions = getline(&actions, &n, file);

    size_t numNodes = 0;
    Node* nodes = (Node*)malloc(0);

    n = 0;
    ssize_t lineSize = 0;
    char* line = NULL;
    while (1) {
        lineSize = getline(&line, &n, file);
        if (lineSize == 1) continue;
        if (lineSize == -1) break;

        Node n = {0};

        for (int i = 0; i < lineSize; i++) {
            if (i < 3) {
                n.id += (line[i] - 'A') * pow(100, i);
            } else if (7 <= i && i < 10) {
                n.left += (line[i] - 'A') * pow(100, i - 7);
            } else if (12 <= i && i < 15) {
                n.right += (line[i] - 'A') * pow(100, i - 12);
            }

            if (i == 2) {
                n.type = line[i] - 'A';
            }
        }

        numNodes++;
        nodes = (Node*)realloc(nodes, numNodes * sizeof(Node));
        nodes[numNodes - 1] = n;
    }

    free(line);

    qsort(nodes, numNodes, sizeof(Node), compareNodes);

    for (int i = 0; i < numNodes; i++) {
        Node left = {.id = nodes[i].left};
        Node right = {.id = nodes[i].right};
        nodes[i].pLeft = (Node*)bsearch(&left, nodes, numNodes, sizeof(Node), compareNodes);
        nodes[i].pRight = (Node*)bsearch(&right, nodes, numNodes, sizeof(Node), compareNodes);
    }

    int aCount = 0;
    while (nodes[aCount].type == 0) {
        aCount++;
    }

    int currAction = 0;
    Node** currNodes = (Node**)malloc(aCount * sizeof(Node**));
    longlong* zLoop = (longlong*)malloc(aCount * sizeof(longlong));
    for (int i = 0; i < aCount; i++) {
        currNodes[i] = &(nodes[i]);
        zLoop[i] = 0;
    }

    longlong currSteps = 0;
    longlong maxZ = 0;
    int distancesFound = 0;
    while (distancesFound < aCount) {
        int zCount = 0;
        for (int i = 0; i < aCount; i++) {
            switch (actions[currAction]) {
                case 'R':
                    currNodes[i] = currNodes[i]->pRight;
                    break;
                case 'L':
                    currNodes[i] = currNodes[i]->pLeft;
                    break;
                default:
                    puts("SUS");
                    break;
            }
            if (currNodes[i]->type == 25) {
                if (zLoop[i] == 0) {
                    zLoop[i] = -currSteps;
                    printf("Found initial z for path %d: %d\n", i, currSteps);
                    if (maxZ < currSteps) {
                        maxZ = currSteps;
                    }
                } else if (zLoop[i] < 0) {
                    zLoop[i] += currSteps;
                    distancesFound++;
                    printf("Found loop for %d (total: %d): %d\n", i, distancesFound, zLoop[i]);
                }
            }
        }
        currSteps++;

        if (currAction < numActions - 2) {
            currAction++;
        } else {
            currAction = 0;
        }
    }

    longlong currLCM = zLoop[0];
    for (int i = 1; i < aCount; i++) {
        currLCM = lcm(currLCM, zLoop[i]);
    }

    free(actions);
    free(nodes);
    free(zLoop);
    printf("%llu\n", currLCM);
}
