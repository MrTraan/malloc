/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:01:01 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/13 20:14:55 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/mman.h>

# define TINY_ALLOC (getpagesize() * 64)
# define SMALL_ALLOC (getpagesize() * 512)

# define TINY_BLOCK 1024
# define SMALL_BLOCK (TINY_BLOCK * 16)
# define HEADER_SIZE (sizeof(t_block))
# define ALIGN_SIZE_8(x) ((((x - 1) >> 3) << 3) + 8)
# define ALIGN_SIZE_4096(x) ((((x - 1) >> 12) << 12) + 4096)

typedef unsigned int t_ui;

typedef enum 				e_alloc_type
{
	TINY,
	SMALL,
	LARGE
}							t_alloc_type;

typedef enum				e_bool
{
	FALSE = 0,
	TRUE = 1
}							t_bool;

typedef struct				s_block
{
	t_ui					size;
	t_bool					is_free;
	struct s_block			*next;
	void					*data;
}							t_block;

typedef struct				s_alloc_manager
{
	void					*tiny_heap;
	void					*small_heap;
	void					*large_heap;
	t_bool					is_init;
}							t_alloc_manager;

extern t_alloc_manager		g_alloc_manager;
extern pthread_mutex_t		g_locker;

void						*malloc(size_t size);
void						free(void *addr);
void						*realloc(void *addr, size_t size);
void						*malloc_unsafe(size_t size);
void						free_unsafe(void *addr);
void						*realloc_unsafe(void *addr, size_t size);

int							init_alloc_manager(void);
t_block						*grow_heap(t_alloc_type type);

void 						remove_large_block(t_block *block);
void						split_block(t_block *block, size_t size);
t_block						*find_existing_block(t_block *heap, size_t size);
void						*find_block(t_block *heap, size_t size, t_alloc_type type);
void						*create_large_block(size_t size);

void						show_alloc_mem(void);

#endif
