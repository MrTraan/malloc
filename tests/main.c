/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:29:13 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/13 20:29:23 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void	test_malloc_simple()
{
	void *holder[54];
	char *r;
	char *r2;

	for (int i = 0; i < 50; i++){
		char *str1 = (char *)malloc(10);
		strcpy(str1, "hello");
		holder[i] = str1;
		if (i == 35) {
			r = str1;
			holder[i] = NULL;
		}
	}
	for (int i = 0; i < 3; i++) {
		char *str2 = (char *)malloc(1024);
		strcpy(str2, "WORLD");
		holder[i + 50] = str2;
		if (i == 1) {
			r2 = str2;
			holder[i + 50] = NULL;
		}
	}
	holder[53] = malloc(10000);
	free(r);
	free(r2);

	printf("\nBEFORE CLEANUP:\n");
	printf("\n=============\n");
	show_alloc_mem();
	printf("\n=============\n");

	for (int i = 0; i < 54; i++)
		free(holder[i]);
	printf("\nAFTER CLEANUP:\n");
	printf("\n=============\n");
	show_alloc_mem();
	printf("\n=============\n");
}

void	test_realloc_simple()
{
	char *s1 = malloc(10);
	char *s2 = malloc(10);
	strcpy(s1, "hello");
	strcpy(s2, "world");

	printf("\nBEFORE REALLOC\n");
	printf("\n=============\n");
	show_alloc_mem();
	printf("\n=============\n");
	
	s2 = realloc(s2, SMALL_BLOCK + 1);

	printf("\nAFTER REALLOC\n");
	printf("\n=============\n");
	show_alloc_mem();
	printf("\n=============\n");
	free(s1);
	free(s2);
}

void	test_realloc_useless()
{
	char	*s1 = malloc(10);
	strcpy(s1, "hello");

	
	printf("Useless realloc, should not do anything\n");
	printf("\nBEFORE REALLOC\n");
	printf("\n=============\n");
//	show_alloc_mem();
	printf("\n=============\n");
	
	s1 = realloc(s1, 9);

	printf("\nAFTER REALLOC\n");
	printf("\n=============\n");
//	show_alloc_mem();
	printf("\n=============\n");
	free(s1);

}

int		main(void)
{ 
	test_malloc_simple();
	test_realloc_simple();
	test_realloc_useless();
	return (0);
}
