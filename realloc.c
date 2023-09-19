#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @mem: the pointer to the memory area
 * @byte: the byte to fill *mem with
 * @size: the number of bytes to be filled
 * Return: (mem) a pointer to the memory area mem
 */
char *_memset(char *mem, char byte, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        mem[i] = byte;
    return mem;
}

/**
 * ffree - frees a string array
 * @str_arr: string array to be freed
 */
void ffree(char **str_arr)
{
    char **p = str_arr;

    if (!str_arr)
        return;
    while (*str_arr)
        free(*str_arr++);
    free(p);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to the previous malloc'ated block
 * @old_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the reallocated block or NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return (new_ptr);
}

