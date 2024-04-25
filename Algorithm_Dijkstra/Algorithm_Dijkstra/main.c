#include <stdio.h>
#include <limits.h>

#define CountVertices	9

typedef struct Path {
	int Dist[CountVertices];
	_Bool Visited[CountVertices];
}Path;

int MinDistance(Path path);
void PrintSolution(Path path);
void Algorithm_Dijkstra(int graph[CountVertices][CountVertices], int StartVertice);

int main() {
	int graph[CountVertices][CountVertices] =
	{
		{0, 4, 0, 0, 0, 0, 0, 8, 0},
		{4, 0, 8, 0, 0, 0, 0, 11, 0},
		{0, 8, 0, 7, 0, 4, 0, 0, 2},
		{0, 0, 7, 0, 9, 14, 0, 0, 0},
		{0, 0, 0, 9, 0, 10, 0, 0, 0},
		{0, 0, 4, 14, 10, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 2, 0, 1, 6},
		{8, 11, 0, 0, 0, 0, 1, 0, 7},
		{0, 0, 2, 0, 0, 0, 6, 7, 0}
	};

	Algorithm_Dijkstra(graph, 0);

	return 0;
}

int MinDistance(Path path) {
	int minimum = INT_MAX, min_index;

	for (int i = 0; i < CountVertices; i++) {
		if (path.Visited[i] == 0 && path.Dist[i] <= minimum) {
			minimum = path.Visited[i];
			min_index = i;
		}
	}

	return min_index;
}

void PrintSolution(Path path) {
	printf("Vertice \t Distance from Source\n");
	for (int i = 0; i < CountVertices; i++)
		printf("%d \t\t %d\n", i, path.Dist[i]);
}

void Algorithm_Dijkstra(int graph[CountVertices][CountVertices], int StartVertice) {
	Path path;

	for (int i = 0; i < CountVertices; i++) {
		path.Dist[i] = INT_MAX;
		path.Visited[i] = 0;
	}

	path.Dist[StartVertice] = 0;

	for (int count = 0; count < CountVertices - 1; count++) {
		int U = MinDistance(path);
		path.Visited[U] = 1;

		for (int V = 0; V < CountVertices; V++)
			if (path.Visited[V] == 0 && graph[U][V] && path.Dist[U] != INT_MAX && path.Dist[U] + graph[U][V] < path.Dist[V])
				path.Dist[V] = path.Dist[U] + graph[U][V];
	}

	PrintSolution(path);
}