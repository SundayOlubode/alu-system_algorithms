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
	vertex_t *new_vertices;
	int i;
	int nb_vertices = graph->nb_vertices;

	if (new_vertex == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < nb_vertices; i++)
	{
		if (strcmp(g_vertex->content, str) == 0)
		{
			free(new_vertex);
			/* free(new_vertices);*/
			return (NULL);
		}
		g_vertex++;
	}

	new_vertex->content = strdup(str);
	if (new_vertex->content == NULL)
	{
		free(new_vertex);
		return (NULL);
	}
	new_vertex->edges = NULL;
	new_vertex->nb_edges = 0;

	new_vertices = realloc(
	    graph->vertices,
	    (graph->nb_vertices + 1) * sizeof(vertex_t));

	if (new_vertices == NULL)
	{
		free(new_vertex->content);
		free(new_vertex);
		return (NULL);
	}

	graph->vertices = new_vertices;
	graph->vertices[graph->nb_vertices++] = *new_vertex;

	return (&graph->vertices[graph->nb_vertices - 1]);
}
