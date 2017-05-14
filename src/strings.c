/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 18:31:45 by ngrasset          #+#    #+#             */
/*   Updated: 2017/05/14 18:47:30 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		ft_putstr(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

void		ft_putendl(char *s)
{
	ft_putstr(s);
	ft_putstr("\n");
}

static void	ft_putdigit(int n)
{
	if (n > 0 && n < 10)
		n += '0';
	else
		n = (n - 10 + 'A');
	write(1, &n, 1);
}

void		ft_putnbr(unsigned long n, int base)
{
	if (n >= (unsigned long)base)
	{
		ft_putnbr(n / base, base);
		ft_putnbr(n % base, base);
	}
	else
		ft_putdigit(n);
}
