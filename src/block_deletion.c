/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_deletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:00:20 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 18:30:34 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void 		remove_large_block(t_block *block)
{
	t_block		*prev;

	prev = find_previous_block(block);
	if (!prev)
		return ;
	if (prev == block)
		g_alloc_manager.large_heap = block->next;
	else
		prev->next = block->next;
	munmap((void *)block, block->size + HEADER_SIZE);
}

static void	optimize_heap(t_block *ptr)
{
	if (!ptr)
		return ;
	while (ptr->is_free == TRUE && ptr->next && ptr->next->is_free == TRUE)
	{
		ptr->size += ptr->next->size + HEADER_SIZE;
		ptr->next = ptr->next->next;
	}
}

static void	remove_empty_pages(t_block *head, size_t size)
{
	t_block		*ptr;
	t_block		*next;

	if (!head)
		return;
	ptr = head->next;
	while (ptr && ptr->next)
	{
		next = ptr->next;
		if (next && next->size == (size - HEADER_SIZE))
		{
			ptr->next = next->next;
			munmap((void *)next, next->size + HEADER_SIZE);
		}
		ptr = ptr->next;
	}
}

void		optimize_memory(void)
{
	optimize_heap((t_block *)g_alloc_manager.tiny_heap);
	optimize_heap((t_block *)g_alloc_manager.small_heap);
	remove_empty_pages((t_block *)g_alloc_manager.tiny_heap, TINY_ALLOC);
	remove_empty_pages((t_block *)g_alloc_manager.small_heap, SMALL_ALLOC);
}
