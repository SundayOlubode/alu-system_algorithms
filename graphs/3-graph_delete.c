#include <stdlib.h>
#include "graphs.h"

void free_edges(vertex_t *vertex);

/**
 * graph_delete - completely deletes a graph.
 * @graph: the graph to delete.
 *
 * Return: void.
 */
void graph_delete(graph_t *graph)
{
	vertex_t *current_vertex = graph->vertices;
	vertex_t *next_vertex;

	while (current_vertex != NULL)
	{
		free_edges(current_vertex);

		next_vertex = current_vertex->next;

		free(current_vertex->content);
		free(current_vertex);

		current_vertex = next_vertex;
	}

	free(graph);
}

/**
 * free_edges - frees all edges of a vertex.
 * @vertex: the vertex whose edges are to be freed.
 *
 * Return: void.
 */
void free_edges(vertex_t *vertex)
{
	edge_t *current_edge = vertex->edges;
	edge_t *next_edge;

	while (current_edge != NULL)
	{
		next_edge = current_edge->next;
		free(current_edge);
		current_edge = next_edge;
	}
}
