/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_deletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:00:20 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/13 20:05:59 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void 		remove_large_block(t_block *block)
{
	t_block		*ptr;

	ptr = (t_block *)g_alloc_manager.large_heap;
	if (!ptr)
		return ;
	if (ptr == block)
		ptr->next = block->next;
	else
	{
		while (ptr)
		{
			if (ptr->next == block)
			{
				ptr->next = block->next;
				break ;
			}
			ptr = ptr->next;
		}
	}
	if (!ptr)
		return ;
	munmap((void *)block, block->size + HEADER_SIZE);
}
