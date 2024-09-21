#include <stdlib.h>
#include <string.h>
#include "graphs.h"

vertex_t *get_vertex(graph_t *graph, const char *src);
edge_t *create_edge(vertex_t *src_vertex,
		    vertex_t *dest_vertex, edge_type_t type);

/**
 * graph_add_edge - adds an edge to two vertices in the given graph.
 * @graph: the graph.
 * @src: the string identifying the vertex to make the connection from.
 * @dest: the string identifying the vertex to connect to.
 * @type: the type of edge.
 *
 * Return: 1 | 0
 */
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
	vertex_t *src_vertex, *dest_vertex;
	edge_t *edge;

	if (graph == NULL || src == NULL || dest == NULL)
	{
		return (0);
	}
	if (type != UNIDIRECTIONAL && type != BIDIRECTIONAL)
	{
		return (0);
	}

	/*find src vertex*/
	src_vertex = get_vertex(graph, src);
	if (src_vertex == NULL)
	{
		return (0);
	}

	/*find dest vertex*/
	dest_vertex = get_vertex(graph, dest);
	if (dest_vertex == NULL)
	{
		return (0);
	}

	/*connect edge*/
	edge = create_edge(src_vertex, dest_vertex, type);
	if (edge == NULL)
	{
		return (0);
	}

	src_vertex->nb_edges += 1;
	dest_vertex->nb_edges += 1;

	return (1);
}

/**
 * get_vertex - get a vertex with the content string.
 *
 * @graph: grapgh to traverse.
 * @str: string to search for.
 *
 * Return: vertex | NULL.
 */
vertex_t *get_vertex(graph_t *graph, const char *str)
{
	vertex_t *g_vertex = graph->vertices;

	while (g_vertex != NULL)
	{
		if (strcmp(g_vertex->content, str) == 0)
		{
			return (g_vertex);
		}
		g_vertex = g_vertex->next;
	}

	free(g_vertex);
	return (NULL);
}

/**
 * create_edge - creates an edge
 *
 * @src_vertex: source vertex.
 * @dest_vertex: destination vertex.
 * @type: BIDIRECTIONAL | UNIDIRECTIONAL.
 *
 * Return: egde pointer | NULL.
 */
edge_t *create_edge(vertex_t *src_vertex,
		    vertex_t *dest_vertex, edge_type_t type)
{
	edge_t *edge = malloc(sizeof(edge_t));

	if (edge == NULL)
	{
		return (NULL);
	}

	edge->dest = dest_vertex;
	edge->next = NULL;

	if (type == BIDIRECTIONAL)
	{

		edge_t *reverse_edge = malloc(sizeof(edge_t));

		if (reverse_edge == NULL)
		{
			free(edge);
			return (NULL);
		}

		reverse_edge->dest = src_vertex;
		reverse_edge->next = dest_vertex->edges;
		dest_vertex->edges = reverse_edge;
	}

	edge->next = src_vertex->edges;
	src_vertex->edges = edge;

	return (edge);
}
