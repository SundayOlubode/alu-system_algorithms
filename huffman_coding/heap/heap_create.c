#include <stdlib.h>
#include "heap.h"

/**
 * heap_create - Creates a Heap data structure
 * @data_cmp: Pointer to the comparison function
 *
 * Return: Pointer to the created heap_t structure, or NULL if it fails
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	heap = malloc(sizeof(heap_t));
	if (!heap)
		return (NULL);

	heap->root = NULL;
	heap->size = 0;
	heap->data_cmp = data_cmp;

	return (heap);
}
