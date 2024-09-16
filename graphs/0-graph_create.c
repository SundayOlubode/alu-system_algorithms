#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

graph_t *graph_create(void)
{
        graph_t *graph = malloc(sizeof(graph_t));
        vertex_t *vertices;

        if (graph == NULL)
        {
                return (NULL);
        }

        graph->nb_vertices = NULL;
        graph->vertices = vertices;
}
