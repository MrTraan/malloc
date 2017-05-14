/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:43:04 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 18:31:04 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void			split_block(t_block *block, size_t size)
{
	t_block		*new;

	new = (t_block *)(block->data + size);
	new->size = block->size - size - HEADER_SIZE;
	new->next = block->next;
	new->is_free = TRUE;
	new->data = (void *)new + HEADER_SIZE;
	block->size = size;
	block->next = new;
}

t_block			*find_existing_block(t_block *heap, size_t size)
{
	t_block		*ptr;

	ptr = heap;
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		if (ptr->size >= size && ptr->is_free == TRUE)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void			*find_block(t_block *heap, size_t size, t_alloc_type type)
{
	t_block		*res;

	res = find_existing_block(heap, size);
	if (!res)
	{
		if (!(res = grow_heap(type)))
			return (NULL);
		return (find_block(heap, size, type));
	}
	if ((res->size - size) >= (HEADER_SIZE + 8))
		split_block(res, size);
	res->is_free = FALSE;
	return (res->data);
}

void			*create_large_block(size_t size)
{
	t_block		*new;
	size_t		size_aligned;

	size_aligned = ALIGN_SIZE_4096(size);
	if (!(new = (t_block *)mmap(0, size_aligned, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	new->size = size_aligned - HEADER_SIZE;
	new->is_free = FALSE;
	new->next = g_alloc_manager.large_heap;
	new->data = (void *)new + HEADER_SIZE;
	g_alloc_manager.large_heap = new;
	return (new->data);
}
