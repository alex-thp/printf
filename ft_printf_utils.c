/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:10:08 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/08 17:35:53 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_do_int(int nb, t_list *tab)
{
	unsigned int	i;

	i = nb;
	if (nb < 0)
	{
		ft_putchar_fd('-', 1);
		tab->count += 1;
		i = -nb;
	}
	if (i < 10)
		ft_putchar_fd((i + 48), 1);
	if (i > 9)
	{
		ft_do_int((i / 10), tab);
		ft_putchar_fd((i % 10) + 48, 1);
	}
	tab->count += 1;
}

void	ft_do_char(int c, t_list *tab)
{
	ft_putchar_fd((char)c, 1);
	tab->count += 1;
}

void	ft_do_string(char *str, t_list *tab)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		tab->count += 1;
		i++;
	}
}

void	ft_do_unsigned_int(unsigned int nb, t_list *tab)
{
	if (nb < 10)
		ft_putchar_fd((nb + 48), 1);
	if (nb > 9)
	{
		ft_do_unsigned_int((nb / 10), tab);
		ft_putchar_fd((nb % 10) + 48, 1);
	}
	tab->count += 1;
}

void	ft_do_hexa(unsigned int nb, t_list *tab, char c)
{
	char			*base;
	unsigned int	i;

	if (c == 'x')
		base = "0123456789abcdef\0";
	else
		base = "0123456789ABCDEF\0";
	i = nb;
	if (nb < 0)
	{
		ft_putchar_fd('-', 1);
		tab->count += 1;
		i = -nb;
	}
	if (i < 17)
		ft_putchar_fd(base[i], 1);
	if (i > 16)
	{
		ft_do_hexa(i / 16, tab, c);
		ft_putchar_fd(base[i % 16], 1);
	}
	tab->count += 1;
}

void	ft_do_address(unsigned long i, t_list *tab, int j)
{
	char	*base;

	base = "0123456789abcdef\0";
	if (j == 0)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd('x', 1);
		tab->count += 2;
	}
	if (i < 17)
		ft_putchar_fd(base[i], 1);
	if (i > 16)
	{
		ft_do_address(i / 16, tab, i + 1);
		ft_putchar_fd(base[i % 16], 1);
	}
	tab->count += 1;
}
