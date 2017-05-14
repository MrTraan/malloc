/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:11:03 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 18:57:18 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_alloc_manager		g_alloc_manager = {
	NULL,
	NULL,
	NULL,
	FALSE
};

pthread_mutex_t		g_locker;

int					init_alloc_manager(void)
{
	t_block			*new;

	if (!(g_alloc_manager.tiny_heap = mmap(0, TINY_ALLOC,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (1);
	new = (t_block *)g_alloc_manager.tiny_heap;
	new->size = TINY_ALLOC - HEADER_SIZE;
	new->next = NULL;
	new->is_free = TRUE;
	new->data = (void *)new + HEADER_SIZE;
	if (!(g_alloc_manager.small_heap = mmap(0, SMALL_ALLOC,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (1);
	new = (t_block *)g_alloc_manager.small_heap;
	new->size = SMALL_ALLOC - HEADER_SIZE;
	new->next = NULL;
	new->is_free = TRUE;
	new->data = (void *)new + HEADER_SIZE;
	return (0);
}

static void			register_new_block(t_block *new, void **heap)
{
	t_block		*ptr;

	ptr = (t_block *)*heap;
	if (!ptr)
	{
		*heap = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_block				*grow_heap(t_alloc_type type)
{
	t_block			*new;
	size_t			size;

	size = (type == TINY ? TINY_ALLOC : SMALL_ALLOC);
	if (!(new = mmap(0, TINY_ALLOC, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	new->size = size - HEADER_SIZE;
	new->next = NULL;
	new->is_free = TRUE;
	new->data = (void *)new + HEADER_SIZE;
	if (type == TINY)
		register_new_block(new, &(g_alloc_manager.tiny_heap));
	if (type == SMALL)
		register_new_block(new, &(g_alloc_manager.small_heap));
	return (new);
}
