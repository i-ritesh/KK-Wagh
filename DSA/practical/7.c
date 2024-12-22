#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10  // Maximum number of nodes (intersections)

// Structure to represent a node in an adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure to represent the graph (city map)
typedef struct Graph {
    Node* adjList[MAX_NODES];  // Adjacency list for each node
    bool visited[MAX_NODES];    // Visited array for traversal
} Graph;

// Function to initialize the graph
void initGraph(Graph* g) {
    for (int i = 0; i < MAX_NODES; i++) {
        g->adjList[i] = NULL;
        g->visited[i] = false;
    }
}

// Function to add an edge to the graph (city map)
void addEdge(Graph* g, int src, int dest) {
    // Create a new node for the destination
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;

    // Create a new node for the source (if undirected graph)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = g->adjList[dest];
    g->adjList[dest] = newNode;
}

// Depth First Search (DFS) algorithm
void DFS(Graph* g, int vertex) {
    // Mark the current node as visited
    g->visited[vertex] = true;
    printf("%d ", vertex);  // Print the current vertex

    // Visit all the adjacent nodes
    Node* temp = g->adjList[vertex];
    while (temp) {
        int adjacentVertex = temp->vertex;
        if (!g->visited[adjacentVertex]) {
            DFS(g, adjacentVertex);
        }
        temp = temp->next;
    }
}

// Breadth First Search (BFS) algorithm
void BFS(Graph* g, int startVertex) {
    bool queue[MAX_NODES];
    int front = 0, rear = 0;
    int queueArray[MAX_NODES];
    
    // Initialize visited array and queue
    for (int i = 0; i < MAX_NODES; i++) {
        queue[i] = false;
    }
    
    queue[rear] = true;
    queueArray[rear] = startVertex;
    rear++;
    g->visited[startVertex] = true;

    while (front != rear) {
        int currentVertex = queueArray[front];
        front++;
        printf("%d ", currentVertex);  // Print the current vertex
        
        // Explore adjacent vertices
        Node* temp = g->adjList[currentVertex];
        while (temp) {
            int adjacentVertex = temp->vertex;
            if (!g->visited[adjacentVertex]) {
                queue[rear] = true;
                queueArray[rear] = adjacentVertex;
                rear++;
                g->visited[adjacentVertex] = true;
            }
            temp = temp->next;
        }
    }
}

// Function to reset the visited array before another traversal
void resetVisited(Graph* g) {
    for (int i = 0; i < MAX_NODES; i++) {
        g->visited[i] = false;
    }
}

// Main function
int main() {
    Graph cityMap;
    initGraph(&cityMap);

    // Adding some example roads (edges) between intersections (nodes)
    // These values represent roads between intersections in the city
    addEdge(&cityMap, 0, 1);  // Road between intersection 0 and 1
    addEdge(&cityMap, 0, 2);  // Road between intersection 0 and 2
    addEdge(&cityMap, 1, 3);  // Road between intersection 1 and 3
    addEdge(&cityMap, 1, 4);  // Road between intersection 1 and 4
    addEdge(&cityMap, 2, 5);  // Road between intersection 2 and 5
    addEdge(&cityMap, 3, 6);  // Road between intersection 3 and 6
    addEdge(&cityMap, 4, 7);  // Road between intersection 4 and 7
    addEdge(&cityMap, 5, 8);  // Road between intersection 5 and 8
    addEdge(&cityMap, 6, 9);  // Road between intersection 6 and 9

    int startVertex;

    // Depth First Search (DFS)
    printf("Enter the starting intersection for DFS: ");
    scanf("%d", &startVertex);
    printf("DFS Traversal starting from intersection %d:\n", startVertex);
    DFS(&cityMap, startVertex);
    resetVisited(&cityMap);  // Reset visited array

    // Breadth First Search (BFS)
    printf("\nEnter the starting intersection for BFS: ");
    scanf("%d", &startVertex);
    printf("BFS Traversal starting from intersection %d:\n", startVertex);
    BFS(&cityMap, startVertex);

    return 0;
}
