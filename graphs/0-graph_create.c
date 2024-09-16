#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - creates a grapgh and initialize it.
 * Return: pointer to a graph.
 */
graph_t *graph_create(void)
{
        graph_t *graph = malloc(sizeof(graph_t));

        if (graph == NULL)
        {
                return (NULL);
        }

        graph->nb_vertices = 0;
        graph->vertices = NULL;

        return (graph);
}
