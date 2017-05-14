/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:13:14 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 18:55:53 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	print_addr(void *addr)
{
	ft_putstr("0x");
	ft_putnbr((size_t)addr, 16);
}

void	print_alloc_info(t_block *b)
{
	print_addr((void *)(b->data));
	ft_putstr(" - ");
	print_addr((void *)(b->data + b->size));
	ft_putstr(" : ");
	ft_putnbr((int)b->size, 10);
	ft_putendl(" octets");
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
	t_block				*b;
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
	ft_putnbr(total, 10);
	ft_putendl(" octets");
}
