/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_deletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:00:20 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/20 14:14:43 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		remove_large_block(t_block *block)
{
	t_block		*prev;

	if (block && block == g_alloc_manager.large_heap)
	{
		g_alloc_manager.large_heap = block->next;
		munmap((void *)block, block->size + HEADER_SIZE);
		return ;
	}
	prev = find_previous_block(block);
	if (!prev)
		return ;
	prev->next = block->next;
	munmap((void *)block, block->size + HEADER_SIZE);
}

static void	optimize_heap(t_block *block)
{
	size_t		max_size;

	if (block->size <= (t_ui)TINY_BLOCK)
		max_size = TINY_BLOCK;
	else if (block->size <= (t_ui)SMALL_BLOCK)
		max_size = SMALL_BLOCK;
	else
		return ;
	if (block && block->next && block->next->is_free == TRUE &&
			(block->size + block->next->size + HEADER_SIZE) <= max_size)
	{
		block->size += block->next->size + HEADER_SIZE;
		block->next = block->next->next;
	}
}

void		optimize_memory(t_block *block)
{
	optimize_heap(block);
}
