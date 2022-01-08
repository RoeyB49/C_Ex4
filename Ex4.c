
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 99
#define MAX 10
//int arr[10][10], completed[10], n, cost = 0;
int tspAns;

typedef struct edge {
    int src, dest, weight;
    struct edge *next;
} edge;

typedef struct node {
    int key;
    edge *headEdge;
    struct node *next;
} node;

typedef struct graph {
    int size;
    node *headNode;
} graph;

node *createNode(int key) {
    node *newNode = malloc(sizeof(node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

edge *createEdge(int src, int dest, int weight) {
    edge *newEdge = malloc(sizeof(edge));
    newEdge->src = src;
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

graph *createGraph(int size) {
    graph *g = malloc(sizeof(graph));
    g->size = size;
    g->headNode = malloc(size * sizeof(node *));
    g->headNode = NULL;
//    g->headNode->headEdge = malloc(size * sizeof(edge *));
//    g->headNode->headEdge = NULL;
    return g;
}

void removeEdge(graph *g, node *n, int dest);

void addNode(graph *g, int key) {
    node *newNode = createNode(key);
    if (g->headNode == NULL) {
        g->headNode = newNode;
        return;
    }
    node *temp = g->headNode;
    while (temp->next != NULL) {
        if (temp->key == key) {
            temp->headEdge = NULL;
            return;
        }
        temp = temp->next;
    }
    temp->next = newNode;
    ///// resize **************************
//    realloc(g, g->size++);


}

void connect(graph *g, int src, int dest, int weight) {
    edge *newEdge = createEdge(src, dest, weight);
    node *tempNode = g->headNode;
    while (tempNode->next != NULL) {
        if (tempNode->key == src) {
            if (tempNode->headEdge == NULL) {
                tempNode->headEdge = newEdge;
                return;
            }
            edge *tempEdge = tempNode->headEdge;
            while (tempEdge->next != NULL) {
                tempEdge = tempEdge->next;
            }
            tempEdge->next = newEdge;
        }
        tempNode = tempNode->next;
    }
    //

    if (tempNode->key == src) {
        if (tempNode->headEdge == NULL) {
            tempNode->headEdge = newEdge;
            return;
        }
        edge *tempEdge = tempNode->headEdge;
        while (tempEdge->next != NULL) {
            tempEdge = tempEdge->next;
        }
        tempEdge->next = newEdge;
    }

}

void removeEdge(graph *g, node *n, int dest) {
    edge *tempedge = n->headEdge, *prevEdge;
    if (tempedge != NULL && tempedge->dest == dest) {
        n->headEdge = tempedge->next;
        free(tempedge);
//        realloc(g, g->size--);
        return;
    }
    while (tempedge != NULL && tempedge->dest != dest) {
        prevEdge = tempedge;
        tempedge = tempedge->next;
    }
    if (tempedge == NULL)
        return;
    prevEdge->next = tempedge->next;
//    realloc(g, g->size--);
    free(tempedge);
}

void removeNode(graph *g, int key) {
    node *tempNode = g->headNode, *prevNode;
    while (1) {
        if (tempNode != NULL && tempNode->key == key) {
            g->headNode = tempNode->next;
            free(tempNode);
            g = realloc(g, g->size--);
            break;
        }
        while (tempNode != NULL && tempNode->key != key) {
            prevNode = tempNode;
            tempNode = tempNode->next;
        }
        if (tempNode == NULL)
            break;
        prevNode->next = tempNode->next;
        g = realloc(g, g->size--);
        free(tempNode);
        break;
    }
    // **** remove in-headEdge ****
    tempNode = g->headNode;
    if (tempNode == NULL) {
        return;
    }
    while (tempNode->next != NULL) {
        edge *tempEdge = tempNode->headEdge, *prevEdge = NULL, *nextEdge = NULL;
        if (tempEdge == NULL) {
            tempNode = tempNode->next;
            continue;
        }
        while (tempEdge->next != NULL) {
            if (tempEdge->dest == key) {
                removeEdge(g, tempNode, key);
            }
            prevEdge = tempEdge;
            tempEdge = tempEdge->next;
            nextEdge = tempEdge->next;
        }
        if (tempEdge->dest == key) {
            removeEdge(g, tempNode, key);
            free(tempEdge);
            free(prevEdge);
            free(nextEdge);
        }
        tempNode = tempNode->next;
    }
}


void printGraph(graph *g) {
    printf("\ngraph size = %d\n", g->size);
    node *tempNode = g->headNode;
    if (tempNode == NULL)
        return;
    while (tempNode->next != NULL) {
        printf("%d: ", tempNode->key);
        edge *tempEdge = tempNode->headEdge;
        if (tempEdge == NULL) {
            tempNode = tempNode->next;
            printf("\n");
            continue;
        }
        while (tempEdge->next != NULL) {
            printf(" (%d, %d, %d) ", tempEdge->src, tempEdge->dest, tempEdge->weight);
            tempEdge = tempEdge->next;
        }
        printf(" (%d, %d, %d) ", tempEdge->src, tempEdge->dest, tempEdge->weight);

        printf("\n");
        tempNode = tempNode->next;
    }
    printf("%d: ", tempNode->key);
    edge *tempEdge = tempNode->headEdge;
    if (tempEdge == NULL) {
        tempNode = tempNode->next;
        printf("\n");
        return;
    }
    while (tempEdge->next != NULL) {
        printf(" (%d, %d, %d) ", tempEdge->src, tempEdge->dest, tempEdge->weight);
        tempEdge = tempEdge->next;
    }
    printf(" (%d, %d, %d) ", tempEdge->src, tempEdge->dest, tempEdge->weight);
}

int shortestPath(graph *g, int src, int dest) {
    int cost[MAX][MAX];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cost[i][j] = INFINITY;
        }
    }
    node *tempNode = g->headNode;
    if (tempNode == NULL)
        return -1;
    while (tempNode->next != NULL) {
        edge *tempEdge = tempNode->headEdge;
        if (tempEdge == NULL) {
            tempNode = tempNode->next;
            continue;
        }
        while (tempEdge->next != NULL) {
            cost[tempEdge->src][tempEdge->dest] = tempEdge->weight;
            tempEdge = tempEdge->next;
        }
        cost[tempEdge->src][tempEdge->dest] = tempEdge->weight;
        tempNode = tempNode->next;
    }
    edge *tempEdge = tempNode->headEdge;
    if (tempEdge == NULL) {
        tempNode = tempNode->next;
    } else {
        while (tempEdge->next != NULL) {
            cost[tempEdge->src][tempEdge->dest] = tempEdge->weight;
            tempEdge = tempEdge->next;
        }
        cost[tempEdge->src][tempEdge->dest] = tempEdge->weight;
    }


//    // **** printing the matrix for self check ****
//    int row, columns;
//    for (row = 0; row < 10; row++) {
//        for (columns = 0; columns < 10; columns++) {
//            printf("%d     ", cost[row][columns]);
//        }
//        printf("\n");
//    }

    if (cost[src][dest] == INFINITY)
        return -1;

/*
 *      Dijkstra Algorithm:
 */
    int dist[MAX], selected[MAX] = {0};
    for (int i = 0; i < MAX; i++) {
        dist[i] = INFINITY;
  //      prev[i] = -1;
    }
    int start = src;
    selected[start] = 1;
    dist[start] = 0;
    while (selected[dest] == 0) {
        int min = INFINITY;
        int m = 0;
        for (int i = 0; i < MAX; i++) {
            int d = dist[start] + cost[start][i];
            if (d < dist[i] && selected[i] == 0) {
                dist[i] = d;
     //           prev[i] = start;
            }
            if (min > dist[i] && selected[i] == 0) {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    if (dist[dest] == INFINITY)
        return -1;
    return dist[dest];
}

void permute(graph *g, int a[], int size, int l, int r) {
    int i;
    if (l == r) {
        int temp2 = INFINITY;
//        for (int j = 0; j < size; j++)
//            printf("%d, ", a[j]);
//        printf("\n");
        int tempAns = 0;
        for (int j = 0; j <= size - 2; j++) {
//            printf("j = %d\n", j);
            int x = shortestPath(g, a[j], a[j + 1]);
//            printf("x = %d\n", x);
            if (x == -1) {
                tempAns = INFINITY;
                break;
            }
            tempAns += x;
//            tempAns += shortestPath(g, a[j], a[j + 1]);
        }
//        printf("%d\n", tempAns);
        if (tempAns < temp2) {
            tspAns = tempAns;
        }

//        printf("\nTSP shortest path: %d", tspAns);
    } else {
        for (i = l; i <= r; i++) {
//            swap((a + l), (a + i));
            int temp;
            temp = a[l];
            a[l] = a[i];
            a[i] = temp;
            permute(g, a, size, l + 1, r);
//            swap((a + l), (a + i)); //backtrack
            temp = a[l];
            a[l] = a[i];
            a[i] = temp;
        }
    }
}


graph *a(graph *g, char str[]) {
//    printf("%s\n", str);
    g = createGraph(str[0] - '0');
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == 'n')
            addNode(g, str[i + 1] - '0');
    }
    int j, k;
    for (int i = 2; i < strlen(str) - 1; i++) {
        j = i + 1;
        k = i + 2;
        while (str[j] != 'n') {
            connect(g, str[i] - '0', str[j] - '0', str[k] - '0');
            j += 2;
            k += 2;
        }
        i = j;
    }
//    printGraph(g);
    return g;
}

graph *b(graph *g, char str[]) {
//    5 0 4 2 1
    addNode(g, str[0] - '0');
    int j, k;
    j = 1;
    k = 2;
    while (k < strlen(str)) {
        connect(g, str[0] - '0', str[j] - '0', str[k] - '0');
        j += 2;
        k += 2;
    }
//    printGraph(g);
//    printf("%s\n", str);

    return g;
}

graph *d(graph *g, char str[]) {
    removeNode(g, str[0] - '0');
//    printGraph(g);
    //    printf("%s\n", str);
    return g;

}

void s(graph *g, char str[]) {
    printf("Dijsktra shortest path: %d \n", shortestPath(g, str[0] - '0', str[1] - '0'));
}

void t(graph *g, char str[]) {
//    printf("%s\n", str);
////    int temp[strlen(str) - 2];
//    for (int i = 1; i < strlen(str); i++) {
//        int tempMin = tsp(g, str[i] - '0');
//        if (tempMin < min) {
//            min = tempMin;
//        }
//    }
//    printf("\nTSP shortest path: %d", min);
    int temp[strlen(str) - 1];
    int j = 0;
    for (int i = 1; i < strlen(str); i++) {
        temp[j] = str[i] - '0';
        j++;
    }
//    temp[j] = '\0';
    tspAns = -1;
    permute(g, temp, j, 0, j - 1);
    if (tspAns == INFINITY) {
        printf("TSP shortest path: %d \n", -1);
    } else {
        printf("TSP shortest path: %d \n", tspAns);
    }
}

int main() {

    int max = 1024;
    char temp[max], input[max];
    char A[max], B[max], D[max], S[max], T[max];
    scanf("%[^\n]s", temp);
    int i;
    int j = 0;
//    size_t size = 0;
//    size = strlen(temp);
    for (i = 0; i < sizeof(temp); i++) {
        if (temp[i] != 32) {
            input[j] = temp[i];
            j++;
        }
    }
    input[i] = '\0';
    if (input[0] != 'A')
        return 0;
    graph *g = createGraph(input[1] - '0');
    i = 0;

    while (i < strlen(input)) {
        if (input[i] == 'A') {
            j = 0;
            i++;
            while ((input[i] >= '0' && input[i] <= '9') || input[i] == 'n') {
                A[j] = input[i];
                j++;
                i++;
            }
            A[j] = '\0';
            g = a(g, A);
        } else if (input[i] == 'B') {
            j = 0;
            i++;
            while ((input[i] >= '0' && input[i] <= '9')) {
                B[j] = input[i];
                j++;
                i++;
            }
            B[j] = '\0';
            b(g, B);
        } else if (input[i] == 'D') {
            j = 0;
            i++;
            while ((input[i] >= '0' && input[i] <= '9')) {
                D[j] = input[i];
                j++;
                i++;
            }
            D[j] = '\0';
            d(g, D);
        } else if (input[i] == 'S') {
            j = 0;
            i++;
            while ((input[i] >= '0' && input[i] <= '9')) {
                S[j] = input[i];
                j++;
                i++;
            }
            S[j] = '\0';
            s(g, S);
        } else if (input[i] == 'T') {
            j = 0;
            i++;
            while ((input[i] >= '0' && input[i] <= '9')) {
                T[j] = input[i];
                j++;
                i++;
            }
            T[j] = '\0';
            t(g, T);
        }
    }
    return 0;
}
