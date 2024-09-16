#include <stdlib.h>
#include <string.h>
#include "graphs.h"

vertex_t *graph_add_new_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex = malloc(sizeof(vertex_t));
	vertex_t *g_vertex = graph->vertices;
	int i;

	if (new_vertex == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < graph->nb_vertices; i++)
	{
		if (*(g_vertex->content) == *str)
		{
			free(g_vertex);
			return (NULL);
		}
		g_vertex++;
	}

	strcpy(new_vertex->content, str);
	new_vertex->edges = NULL;
	new_vertex->nb_edges = 0;

	vertex_t *new_vertices = realloc(graph->vertices, (graph->nb_vertices + 1) * sizeof(vertex_t));
	if (new_vertices == NULL)
	{
		free(new_vertex->content);
		free(new_vertex);
		return (NULL);
	}

	graph->vertices = new_vertices;
	graph->vertices[graph->nb_vertices++] = *new_vertex;

	return (new_vertex);
}