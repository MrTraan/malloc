/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_unsafe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:27:33 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/13 19:56:17 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void				*malloc_unsafe(size_t size)
{
	size_t 			size_aligned;

	size_aligned = ALIGN_SIZE_8(size);
	if (size_aligned <= TINY_BLOCK)
		return (find_block(g_alloc_manager.tiny_heap, size_aligned, TINY));
	if (size_aligned <= SMALL_BLOCK)
		return (find_block(g_alloc_manager.small_heap, size_aligned, SMALL));
	return (create_large_block(size));
}

void				free_unsafe(void *addr)
{
	t_block		*block;

	block = (t_block *)(addr - HEADER_SIZE);
	block->is_free = TRUE;
	if (block->size > SMALL_BLOCK)
		return (remove_large_block(block));
}

void				*realloc_unsafe(void *addr, size_t size)
{
	free_unsafe(addr);
	return malloc_unsafe(size);
	// invalid
}
