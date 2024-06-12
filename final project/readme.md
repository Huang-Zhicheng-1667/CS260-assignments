Game Map Generator

1. Introduction

Project goal: use C language to create a simple game map generator.
Techniques used: spanning trees, graph structures, Prim's algorithm, and shortest paths.

2. Map Design

Map size: 20*20
Entrance Coordinates: 0,0
Exit Coordinates: 19,19
Obstacles: some obstacles are randomly generated in the middle of the map.

3. Data Structure

Use graph structures to store map data
Each node represents a location on the map
Edges represent connections between locations
Information contained in the node: coordinates, whether it is an obstacle, etc.

4. Map Generation Algorithm

Initialize the map: Create an empty 20x20 map and add entrance and exit coordinates
Randomly add obstacles: Randomly generate a certain number of obstacles in the middle of the map
Print map: Print the map and show it to the user

5. Path finding algorithm

Find the minimum spanning tree path from entry to exit using Prim's algorithm
Loop to verify if there is a path from ingress to egress
If the path exists, print the path and exit the loop
If the path does not exist, randomly remove an obstacle, update the map data structure, and re-search the path.

6. Main program flow

Initialize the map.
Randomly add obstacles.
Print the map.
Use Prim's algorithm to find paths.
If the path exists, print the path and end the program.
If the path does not exist, random obstacles are removed, the map is updated, and the path search is performed again.
Repeat steps 4 to 6 until find the path.

Tests:

Map Initialization:
Test to ensure that the map is initialized properly with all cells as empty ('.').

Obstacle Generation:
Test to verify that obstacles are generated within the map boundaries.
Test to check the density of obstacles.

Minimum Spanning Tree (MST) Generation:
Test to confirm that the generated MST has the correct number of edges.
Test to ensure that the MST edges are within the map boundaries.

Path Existence Check:
Test to validate that the program correctly identifies the existence of a path from the start to the end.
Test to verify the program's behavior when there is no path from the start to the end.

Obstacle Removal:
Test to ensure that a random obstacle is successfully removed from the map.
Test to check if the removal of obstacles maintains connectivity between start and end points.

Implementing

1. Add a new vertex to the graph
The add new vertex function is used to add new vertices to the graph. This function increases the number of vertices in the graph and may require reallocation of adjacency list memory to accommodate the new vertices.

void addVertex(struct Graph* graph, int vertex) {
    if (vertex >= graph->V) {
        graph->V = vertex + 1;
    }
    graph->edges = (struct Edge*)realloc(graph->edges, graph->V * sizeof(struct Edge));
}

2. Add a new edge between two vertices
The add new edge function is used to add new edges to the graph. This function adds new adjacent nodes at the appropriate locations and updates the number of edges.

void addEdge(struct Graph* graph, int src, int dest) {
    if (src >= graph->V || dest >= graph->V) {
        printf("Error: Vertex does not exist.\n");
        return;
    }
    graph->edges[graph->E].src = src;
    graph->edges[graph->E].dest = dest;
    graph->E++;
}

3. A function for a shortest path algorithm
The shortest path algorithm function is used to find the shortest path from a source node to a destination node. The complexity of this function depends on the specific algorithm implementation.

void shortest_path(struct Graph* graph, int source, int destination) {
    ...(Dijkstra)
}

4. A function for a minimum spanning tree algorithm
The Minimum Spanning Tree algorithm function is used to generate the minimum spanning tree of a graph.

struct Graph* min_span_tree(struct Graph* graph) {
    ...(Prim)
}

