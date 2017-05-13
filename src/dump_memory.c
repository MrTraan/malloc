/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:13:14 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/13 20:14:57 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdio.h>
void	print_alloc_info(t_block *b)
{
	printf("%p - %p : %d octets\n", b->data, b->data + b->size, b->size);
	/*
	print_addr((void *)(b->data));
	write(1, " - ", 3);
	print_addr((void *)(b->data + b->size));
	write(1, " : ", 3);
	printf("%d", (int)b->alloc_size);
	write(1, " octets\n", 8);
	*/
}

void	print_addr(void *addr)
{
	printf("%p\n", addr);
}

void	print_memzone(t_block *b, unsigned int *total)
{
	print_addr(b);
	write(1, "\n", 1);
	while (b)
	{
		if (b->is_free == FALSE)
		{
			print_alloc_info(b);
			*total += b->size;
		}
		b = b->next;
	}
}

void	show_alloc_mem(void)
{
	t_block	*b;
	unsigned int		total;

	total = 0;
	b = g_alloc_manager.tiny_heap;
	write(1, "TINY : ", 7);
	print_memzone(b, &total);
	b = g_alloc_manager.small_heap;
	write(1, "SMALL : ", 8);
	print_memzone(b, &total);
	b = g_alloc_manager.large_heap;
	write(1, "LARGE : ", 8);
	print_memzone(b, &total);
	write(1, "Total: ", 7);
	printf("%d octets\n", (int)total);
}

