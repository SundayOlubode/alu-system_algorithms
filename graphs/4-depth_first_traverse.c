#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

#define UNVISITED 0
#define VISITED 1

/**
 * depth_first_util - Recursive helper function for depth-first traversal.
 * @vertex: The current vertex being visited.
 * @visited: Array to track visited vertices.
 * @action: Function to apply to each visited vertex.
 * @depth: Current depth of the traversal.
 *
 * Return: max_depth.
 */
size_t depth_first_util(const vertex_t *vertex, int *visited,
			void (*action)(const vertex_t *v,
				       size_t depth),
			size_t depth)
{
	const edge_t *edge;
	size_t max_depth = depth;

	visited[vertex->index] = VISITED;

	action(vertex, depth);

	for (edge = vertex->edges; edge != NULL; edge = edge->next)
	{
		if (visited[edge->dest->index] == UNVISITED)
		{
			size_t new_depth =
			    depth_first_util(edge->dest, visited, action, depth + 1);
			if (new_depth > max_depth)
				max_depth = new_depth;
		}
	}

	return (max_depth);
}

/**
 * depth_first_traverse - Goes through a graph using depth-first traversal.
 * @graph: Pointer to the graph to traverse.
 * @action: Function pointer to be called for each visited vertex.
 *
 * Return: The biggest vertex depth, or 0 on failure.
 */
size_t depth_first_traverse(const graph_t *graph,
			    void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_depth = 0;

	if (graph == NULL || action == NULL)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (visited == NULL)
		return (0);

	if (graph->vertices != NULL)
	{
		max_depth =
		    depth_first_util(graph->vertices, visited, action, 0);
	}

	free(visited);

	return (max_depth);
}
