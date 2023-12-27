#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct Node {
    int id;
    int left;
    int right;
} Node;

int compareNodes(const void* a, const void* b) {
    const Node* na = (const Node*)a;
    const Node* nb = (const Node*)b;

    if (na->id < nb->id) return -1;
    if (na->id > nb->id) return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out <filename>\n");
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
        }

        numNodes++;
        nodes = (Node*)realloc(nodes, numNodes * sizeof(Node));
        nodes[numNodes - 1] = n;
    }

    qsort(nodes, numNodes, sizeof(Node), compareNodes);
    int countSteps = 0;
    int currAction = 0;
    Node* currNode = &(nodes[0]);

    while (1) {
        Node key;
        switch (actions[currAction]) {
            case 'R':
                key = (Node){.id = currNode->right};
                break;
            case 'L':
                key = (Node){.id = currNode->left};
                break;
        }
        currNode = (Node*)bsearch(&key, nodes, numNodes, sizeof(Node), compareNodes);
        countSteps++;

        if (currNode->id == 252525) {
            break;
        }

        currAction++;
        if (currAction >= numActions - 1) {
            currAction = 0;
        }
    }

    free(actions);
    free(line);
    free(nodes);
    printf("%d\n", countSteps);
}
