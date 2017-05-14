/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:28:03 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 15:28:13 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static int		init_malloc(void)
{
	if (g_alloc_manager.is_init == TRUE)
		return (0);
	g_alloc_manager.is_init = TRUE;
	pthread_mutex_init(&g_locker, NULL);
	return (init_alloc_manager());
}

void			*malloc(size_t size)
{
	void		*ptr;

	if (size == 0 || init_malloc() != 0)
		return (NULL);
	pthread_mutex_lock(&g_locker);
	ptr = malloc_unsafe(size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}

void			*realloc(void *addr, size_t size)
{
	void		*ptr;

	if (!addr)
		return malloc(size);
	if (size == 0 || init_malloc() != 0)
		return (NULL);
	pthread_mutex_lock(&g_locker);
	ptr = realloc_unsafe(addr, size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}

void			free(void *addr)
{
	if (!addr || init_malloc() != 0)
		return ;
	pthread_mutex_lock(&g_locker);
	free_unsafe(addr);
	pthread_mutex_unlock(&g_locker);
}
