#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

/**
 * enqueue - Adds a vertex to the end of the queue.
 * @queue: Pointer to the pointer of the queue.
 * @vertex: The vertex to enqueue.
 * @depth: The depth of the vertex.
 */
void enqueue(queue_t **queue, vertex_t *vertex, size_t depth)
{
	queue_t *new_node = malloc(sizeof(queue_t));
	queue_t *temp;

	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	if (*queue == NULL)
	{
		*queue = new_node;
	}
	else
	{
		temp = *queue;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

/**
 * dequeue - Removes the front vertex from the queue.
 * @queue: Pointer to the pointer of the queue.
 */
void dequeue(queue_t **queue)
{
	if (*queue != NULL)
	{
		queue_t *temp = *queue;
		*queue = (*queue)->next;
		free(temp);
	}
}

/**
 * process_breadth_first - Performs the actual breadth-first traversal logic.
 * @queue: Pointer to the queue containing vertices to visit.
 * @visited: Array keeping track of visited vertices.
 * @action: Function pointer to be called for each visited vertex.
 * @max_depth: Pointer to store the maximum depth found.
 */
void process_breadth_first(queue_t **queue, int *visited,
			   void (*action)(const vertex_t *v,
					  size_t depth),
			   size_t *max_depth)
{
	vertex_t *current_vertex;
	const edge_t *edge;
	size_t current_depth;

	while (*queue != NULL)
	{
		current_vertex = (*queue)->vertex;
		current_depth = (*queue)->depth;
		dequeue(queue);

		if (visited[current_vertex->index] == 1)
			continue;

		visited[current_vertex->index] = 1;
		action(current_vertex, current_depth);

		if (current_depth > *max_depth)
			*max_depth = current_depth;

		for (edge = current_vertex->edges;
		     edge != NULL; edge = edge->next)
		{
			if (visited[edge->dest->index] == 0)
			{
				enqueue(queue, edge->dest, current_depth + 1);
			}
		}
	}
}

/**
 * breadth_first_traverse - Initializes traversal and manages the queue.
 * @graph: Pointer to the graph to traverse.
 * @action: Function pointer to be called for each visited vertex.
 *
 * Return: The biggest vertex depth, or 0 on failure.
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	int *visited;
	size_t max_depth = 0;
	queue_t *queue = NULL;

	if (graph == NULL || action == NULL || graph->vertices == NULL)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(int));
	if (visited == NULL)
		return (0);

	enqueue(&queue, graph->vertices, 0);
	process_breadth_first(&queue, visited, action, &max_depth);

	free(visited);

	return (max_depth);
}
