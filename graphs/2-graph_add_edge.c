#include <stdlib.h>
#include <string.h>
#include "graphs.h"

vertex_t *get_vertex(graph_t *graph, const char *src);
int create_edge(vertex_t *src_vertex, vertex_t *dest_vertex, edge_type_t type);
edge_t *create_single_edge(vertex_t *dest_vertex);
void append_edge(vertex_t *vertex, edge_t *new_edge);

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
	int edge_is_created;

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
	edge_is_created = create_edge(src_vertex, dest_vertex, type);
	if (edge_is_created == 0)
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

	return (NULL);
}

/**
 * create_edge - creates an edge (unidirectional or bidirectional)
 * between two vertices.
 *
 * @src_vertex: source vertex.
 * @dest_vertex: destination vertex.
 * @type: BIDIRECTIONAL | UNIDIRECTIONAL.
 *
 * Return: 1 on success, 0 on failure.
 */
int create_edge(vertex_t *src_vertex, vertex_t *dest_vertex, edge_type_t type)
{
	edge_t *edge;

	/* Create and append the forward edge */
	edge = create_single_edge(dest_vertex);
	if (edge == NULL)
	{
		return (0);
	}
	append_edge(src_vertex, edge);

	/* Handle bidirectional edges */
	if (type == BIDIRECTIONAL)
	{
		edge_t *reverse_edge = create_single_edge(src_vertex);

		if (reverse_edge == NULL)
		{
			free(edge);
			return (0);
		}
		append_edge(dest_vertex, reverse_edge);
	}

	return (1);
}

/**
 * create_single_edge - creates a single edge between two vertices.
 * @dest_vertex: the destination vertex.
 *
 * Return: pointer to the new edge | NULL.
 */
edge_t *create_single_edge(vertex_t *dest_vertex)
{
	edge_t *edge = malloc(sizeof(edge_t));

	if (edge == NULL)
	{
		return (NULL);
	}

	edge->dest = dest_vertex;
	edge->next = NULL;

	return (edge);
}

/**
 * append_edge - appends a newly created edge to a vertex's edge list.
 * @vertex: the vertex whose edge list will be appended.
 * @new_edge: the edge to append.
 */
void append_edge(vertex_t *vertex, edge_t *new_edge)
{
	if (vertex->edges == NULL)
	{
		vertex->edges = new_edge;
	}
	else
	{
		edge_t *current = vertex->edges;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_edge;
	}
}
