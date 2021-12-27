#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct node {
    int dst;
    int weight;
    struct node *next;
};

struct adjList {
    struct node *head;
};

struct Graph {
    int n;
    struct adjList *array;
};

struct node *createNode(int v) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->dst = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createAGraph(int v) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->n = v;
    graph->array = malloc(v * sizeof(struct node *));
    int i;
    for (i = 0; i < v; i++) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int dst, int weight) {
    // Add edge from src to dst
    struct node *newNode = createNode(dst);
    newNode->weight = weight;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void removeEdge(struct Graph *graph, int v) {
    graph->array[v].head = NULL;
}


void printGraph(struct Graph *g) {
    for (int v = 0; v < g->n; ++v) {
        struct node *ptr = g->array[v].head;
        printf("\n %d\n", v);
        while (ptr) {
            printf("->  %d w:%d", ptr->dst, ptr->weight);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

void A(char str[]) {
    struct Graph *graph = createAGraph(str[0] - '0');
    int j = 0, k = 0;
    for (int i = 2; i < strlen(str) - 1; i++) {
        j = i + 1;
        k = i + 2;
        while (str[j] != 'n') {
            addEdge(graph, str[i] - '0', str[j] - '0', str[k] - '0');
            j += 2;
            k += 2;
        }
        i = j;
    }
//    printGraph(graph);
}

void B(struct Graph *graph, char str[]) {
    if (str[0] - '0' < graph->n) {
        removeEdge(graph, str[0] - '0');
    }
    int i = 0, j = 0, k = 0;
    j = i + 1;
    k = i + 2;
    while (j < strlen(str)) {
        addEdge(graph, str[i] - '0', str[j] - '0', str[k] - '0');
        j += 2;
        k += 2;
    }
    i = j;
}
void D(struct Graph *graph, char str[]) {
    graph->array[str[0] - '0'].head = NULL;
    int i = 0;
    while (i < graph->n) {
        struct node *tmp = graph->array[i].head;
        if(tmp->next==NULL&&tmp->dst == str[0] - '0'){
            tmp=NULL;
        }
        if(tmp!=NULL) {
            while (tmp->next != NULL) {
                if (tmp->dst == str[0] - '0') {
                    if (tmp->next != NULL)
                        tmp = tmp->next;
                    if(tmp->next==NULL)
                        tmp=NULL;
                }
                tmp = tmp->next;
            }
        }
        i++;
    }
}
int main() {
//    struct Graph *graph = createAGraph(3);
//    addEdge(graph, 0, 1, 5);
//    addEdge(graph, 0, 2, 7);
//    addEdge(graph, 1, 0, 9);
//    graph->array[0].head = NULL;
//    printGraph(graph);
    char str[]="4n02533n20411n13702n3";
    struct Graph *graph = createAGraph(str[0] - '0');
    int j = 0, k = 0;
    for (int i = 2; i < strlen(str) - 1; i++) {
        j = i + 1;
        k = i + 2;
        while (str[j] != 'n') {
            addEdge(graph, str[i] - '0', str[j] - '0', str[k] - '0');
            j += 2;
            k += 2;
        }
        i = j;
    }
//    A(str);
    printGraph(graph);
//    char str1[]="01821";
//    B(graph,str1);
//    printGraph(graph);
//    char str1[]="01821";
    char str1[]="2";
    D(graph,str1);
    printGraph(graph);
}