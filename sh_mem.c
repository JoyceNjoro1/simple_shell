#include "main.h"

/**
 * _memcpy - copies information
 * @newptr: dest ptr.
 * @ptr: src ptr.
 * @size: size of ptr
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int x;

	for (x = 0; x < size; x++)
		char_newptr[x] = char_ptr[x];
}

/**
 * _realloc - realloc  mem
 * @ptr: ptr to the mem previously alloc
 * @old_size: siz of the allocated ptr
 * @new_size: new size
 *
 * Return: ptr.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - realloc a memory block.
 * @ptr: double ptr to  mem previously alloc.
 * @old_size: size, of the alloc space of ptr.
 * @new_size: new size, of the new memory block.
 *
 * Return: ptr.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int x;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (x = 0; x < old_size; x++)
		newptr[x] = ptr[x];

	free(ptr);

	return (newptr);
}
