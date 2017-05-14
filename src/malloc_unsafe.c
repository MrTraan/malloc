/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_unsafe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:27:33 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 17:26:30 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static size_t		size_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

static void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*uc_dst;
	unsigned char	*uc_src;

	uc_dst = (unsigned char *)dst;
	uc_src = (unsigned char *)src;
	while (n > 0)
	{
		*uc_dst = *uc_src;
		uc_dst++;
		uc_src++;
		n--;
	}
	return (dst);
}

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

	block = find_block_from_addr(addr);
	if (!block)
		return ;
	if (block->size > SMALL_BLOCK)
		return (remove_large_block(block));
	block->is_free = TRUE;
	optimize_memory();
}

void				*realloc_unsafe(void *addr, size_t size)
{
	t_block			*block;
	void			*new_block;

	block = find_block_from_addr(addr);
	if (!block)
		return (NULL);
	if (block->size >= size)
		return (block->data);
	new_block = malloc_unsafe(size);
	if (!new_block)
		return (NULL);
	ft_memcpy(new_block, block->data, size_min(block->size, size));
	free_unsafe(addr);
	return (new_block);
}
