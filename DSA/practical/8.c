#include <stdio.h>
#include <limits.h>

#define V 6  // Number of nodes in the graph (areas in the city)

// Function to find the node with the minimum distance
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to implement Dijkstra's algorithm to find the shortest path
void dijkstra(int graph[V][V], int src, int dist[]) {
    bool visited[V];  // Visited array to track nodes
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[src] = 0;  // Distance to source is 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);  // Find the node with the minimum distance
        visited[u] = true;  // Mark the selected node as visited

        // Update the distances to the adjacent nodes
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

// Function to print the shortest path distances
void printSolution(int dist[], int src) {
    printf("Shortest distances from source node %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("To area %d: Infinity\n", i);
        } else {
            printf("To area %d: %d\n", i, dist[i]);
        }
    }
}

int main() {
    // Graph represented as an adjacency matrix
    // The distances are in kilometers. 0 means no direct road between areas.
    int graph[V][V] = {
        {0, 5, 0, 0, 0, 0},  // Home (0)
        {5, 0, 10, 0, 0, 0}, // Area 1 (1)
        {0, 10, 0, 7, 0, 0}, // Area 2 (2)
        {0, 0, 7, 0, 2, 1},  // Area 3 (3)
        {0, 0, 0, 2, 0, 6},  // College (4)
        {0, 0, 0, 1, 6, 0}   // Area 5 (5)
    };

    int dist[V];  // Array to store the shortest distances from the source
    dijkstra(graph, 0, dist);  // 0 is the source (Home)
    printSolution(dist, 0);  // Print the shortest distances from Home

    return 0;
}
