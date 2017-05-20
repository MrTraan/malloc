/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 16:50:39 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/20 14:08:16 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block			*find_block_from_addr(void *addr)
{
	t_block		*ptr;

	ptr = g_alloc_manager.tiny_heap;
	while (ptr)
	{
		if (ptr->data == addr)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = g_alloc_manager.small_heap;
	while (ptr)
	{
		if (ptr->data == addr)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = g_alloc_manager.large_heap;
	while (ptr)
	{
		if (ptr->data == addr)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_block			*find_previous_block(t_block *block)
{
	t_block		*ptr;

	if (block->size <= (t_ui)TINY_BLOCK)
		ptr = g_alloc_manager.tiny_heap;
	else if (block->size <= (t_ui)SMALL_BLOCK)
		ptr = g_alloc_manager.small_heap;
	else
		ptr = g_alloc_manager.large_heap;
	if (!ptr)
		return (NULL);
	if (ptr == block)
		return (NULL);
	while (ptr->next)
	{
		if (ptr->next == block)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}
