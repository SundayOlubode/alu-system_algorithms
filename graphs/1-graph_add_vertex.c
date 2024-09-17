#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - add a new vertex to graph.
 * @graph: the graph to a new vertex.
 * @str: string on vertex.
 * Return: newly add vertex | NULL.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex = malloc(sizeof(vertex_t));
	vertex_t *g_vertex = graph->vertices;

	if (new_vertex == NULL)
	{
		return (NULL);
	}

	while (g_vertex != NULL)
	{
		if (strcmp(g_vertex->content, str) == 0)
		{
			free(new_vertex);
			return (NULL);
		}
		g_vertex = g_vertex->next;
	}

	new_vertex->content = strdup(str);
	if (new_vertex->content == NULL)
	{
		free(new_vertex);
		return (NULL);
	}
	new_vertex->index = 0;
	new_vertex->edges = NULL;
	new_vertex->nb_edges = 0;
	new_vertex->next = NULL;

	if (graph->nb_vertices)
	{
		graph->vertices = new_vertex;
	}
	else
	{
		g_vertex = graph->vertices;
		while (g_vertex->next != NULL)
		{
			g_vertex = g_vertex->next;
		}
		g_vertex->next = new_vertex;
		new_vertex->index = g_vertex->index + 1;
	}

	graph->nb_vertices++;

	return (new_vertex);
}
