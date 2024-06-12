#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 20

// Structure to represent an edge in the graph
struct Edge {
    int src, dest;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// Function prototypes
void printMap(char map[][SIZE]);
void generateObstacles(char map[][SIZE]);
bool isPathExists(struct Graph* graph, char map[][SIZE]);
void removeObstacle(char map[][SIZE]);

// Function to initialize a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to find the root of a subset
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two subsets
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to generate the Minimum Spanning Tree (MST) using Prim's algorithm
struct Graph* generateMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]),
          [](const void* a, const void* b) -> int {
              struct Edge* a1 = (struct Edge*)a;
              struct Edge* b1 = (struct Edge*)b;
              return a1->dest - b1->dest;
          });

    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    struct Graph* mst = createGraph(V, e);
    for (i = 0; i < e; ++i) {
        mst->edges[i] = result[i];
    }

    free(subsets);

    return mst;
}

// Function to print the map
void printMap(char map[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

// Function to generate random obstacles on the map
void generateObstacles(char map[][SIZE]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (rand() % 5 == 0) // Adjust probability to change obstacle density
                map[i][j] = '#';
        }
    }
}

// Function to check if there exists a path between source and destination using DFS
bool isPathExistsUtil(int src_x, int src_y, int dest_x, int dest_y, char map[][SIZE], bool visited[][SIZE]) {
    if (src_x < 0 || src_x >= SIZE || src_y < 0 || src_y >= SIZE || map[src_x][src_y] == '#' || visited[src_x][src_y])
        return false;

    visited[src_x][src_y] = true;

    if (src_x == dest_x && src_y == dest_y)
        return true;

    if (isPathExistsUtil(src_x + 1, src_y, dest_x, dest_y, map, visited) ||
        isPathExistsUtil(src_x - 1, src_y, dest_x, dest_y, map, visited) ||
        isPathExistsUtil(src_x, src_y + 1, dest_x, dest_y, map, visited) ||
        isPathExistsUtil(src_x, src_y - 1, dest_x, dest_y, map, visited))
        return true;

    return false;
}

// Function to check if there exists a path between source and destination
bool isPathExists(struct Graph* graph, char map[][SIZE]) {
    bool visited[SIZE][SIZE] = {false};
    return isPathExistsUtil(0, 0, SIZE - 1, SIZE - 1, map, visited);
}

// Function to remove a random obstacle from the map
void removeObstacle(char map[][SIZE]) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (map[x][y] != '#');

    map[x][y] = '.';
}

/*
// Function to perform tests
void runTests() {
    char testMap[SIZE][SIZE];

    // Test Map Initialization
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            assert(testMap[i][j] == '.');
        }
    }
    printf("Map Initialization Test Passed\n");

    // Test Obstacle Generation
    generateObstacles(testMap);
    int obstacleCount = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (testMap[i][j] == '#')
                obstacleCount++;
        }
    }
    assert(obstacleCount > 0); // Obstacles should be generated
    printf("Obstacle Generation Test Passed\n");

    // Test MST Generation
    struct Graph* testGraph = createGraph(SIZE * SIZE, SIZE * SIZE * 2);
    struct Graph* testMST = generateMST(testGraph);
    assert(testMST->E == SIZE * SIZE - 1); // MST edges should be V - 1
    for (int i = 0; i < testMST->E; ++i) {
        int src_x = testMST->edges[i].src / SIZE;
        int src_y = testMST->edges[i].src % SIZE;
        int dest_x = testMST->edges[i].dest / SIZE;
        int dest_y = testMST->edges[i].dest % SIZE;
        assert(src_x >= 0 && src_x < SIZE && src_y >= 0 && src_y < SIZE);
        assert(dest_x >= 0 && dest_x < SIZE && dest_y >= 0 && dest_y < SIZE);
    }
    printf("MST Generation Test Passed\n");

    // Test Path Existence Check
    assert(isPathExists(testMST, testMap)); // A path should exist in the MST
    printf("Path Existence Check Test Passed\n");

    // Test Obstacle Removal
    removeObstacle(testMap);
    bool isConnected = isPathExists(testMST, testMap);
    assert(isConnected); // Removing an obstacle should not disconnect the graph
    printf("Obstacle Removal Test Passed\n");

    free(testGraph->edges);
    free(testGraph);
    free(testMST);
}*/

int main() {
    // runTests();
    char map[SIZE][SIZE];

    // Initialize map
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            map[i][j] = '.';
        }
    }

    // Generate obstacles randomly
    generateObstacles(map);

    printf("Initial Map:\n");
    printMap(map);

    while (true) {
        struct Graph* graph = createGraph(SIZE * SIZE, SIZE * SIZE * 2); // Maximum possible edges for a grid graph

        // Add edges to the graph
        int edge_index = 0;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (i < SIZE - 1) {
                    graph->edges[edge_index].src = i * SIZE + j;
                    graph->edges[edge_index].dest = (i + 1) * SIZE + j;
                    edge_index++;
                }
                if (j < SIZE - 1) {
                    graph->edges[edge_index].src =                    i * SIZE + j;
                    graph->edges[edge_index].dest = i * SIZE + (j + 1);
                    edge_index++;
                }
            }
        }

        struct Graph* mst = generateMST(graph); // Generate MST using Prim's algorithm

        if (isPathExists(mst, map)) { // Check if there exists a path from (0, 0) to (SIZE-1, SIZE-1)
            printf("\nPath Found:\n");
            for (int i = 0; i < mst->E; ++i) {
                int src_x = mst->edges[i].src / SIZE;
                int src_y = mst->edges[i].src % SIZE;
                int dest_x = mst->edges[i].dest / SIZE;
                int dest_y = mst->edges[i].dest % SIZE;
                printf("(%d,%d) -> (%d,%d)\n", src_x, src_y, dest_x, dest_y);
            }
            break; // Exit the loop if path found
        } else {
            removeObstacle(map); // Remove a random obstacle if no path exists
        }

        free(graph->edges);
        free(graph);
        free(mst);
    }

    return 0;
}
