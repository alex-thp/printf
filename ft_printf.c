/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:38:30 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/16 18:14:54 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

t_list	*init_tab(const char *str)
{
	t_list		*tab;

	tab = (t_list*)malloc(sizeof(t_list));
	tab->str = str;
	tab->count = 0;
	tab->index = 0;
	return (tab);
}

int		is_set(char c)
{
	char	*set;
	int		i;

	set = "cspdiuxX";
	i = 0;
	while (set[i])
	{
		if (c == '%' || c == set[i])
			return (i);
		i++;
	}
	return (-1);
}

void	ft_do(t_list *tab)
{
	if (tab->arg == 'd' || tab->arg == 'i')
	{
		if (tab->point != 1 || tab->val_point != 0 || tab->var_int != 0)
			ft_do_int(tab->var_int, tab);
	}
	if (tab->arg == 'x' || tab->arg == 'X')
	{
		if (tab->point != 1 || tab->val_point != 0 || tab->var_ulong != 0)
			ft_do_hexa(tab->var_ulong, tab, tab->arg);
	}
	if (tab->arg == 'p')
		ft_do_address(tab->var_ulong, tab, 0);
	if (tab->arg == 'c')
		ft_do_char(tab->var_int, tab);
	if (tab->arg == 's')
		ft_do_string(tab->var_string, tab);
	if (tab->arg == 'u')
	{
		if (tab->point != 1 || tab->val_point != 0 || tab->var_ulong != 0)
			ft_do_unsigned_int(tab->var_ulong, tab);
	}
	if (tab->arg == '%')
		ft_do_pourcent(tab);
}

void	ft_init_parse(t_list *tab)
{
	tab->moins = 0;
	tab->point = 0;
	tab->zero = 0;
	tab->star = 0;
	tab->precision = 0;
	tab->val_moins = 0;
	tab->val_point = 0;
}

int		ft_printf(const char *str, ...)
{
	t_list		*tab;
	int			i;

	tab = init_tab(str);
	va_start(tab->ap, str);
	while (str[tab->index])
	{
		i = 1;
		if (str[tab->index] == '%')
		{
			ft_init_parse(tab);
			while (is_set(str[tab->index + i]) == -1)
				i++;
			tab->arg = str[tab->index + i];
			parse_zero(tab);
			tab->index += i;
		}
		else
			ft_do_char(str[tab->index], tab);
		tab->index += 1;
	}
	i = tab->count;
	free(tab);
	return (i);
}

#include <stdio.h>

int		main(void)
{
	int i;
	int j;

	i = printf("   printf : %11.4x1kia7tN%08u%-19X7Fx%0*urztKcX\n", 0, 0, 0, -5, -2147483647);
	j = ft_printf("ft_printf : %11.4x1kia7tN%08u%-19X7Fx%0*urztKcX\n", 0, 0, 0, -5, -2147483647);
	printf("i = %d, j = %d\n", i, j);
	i = printf("   printf : cjk7z9IfU0%-5cg8DsSS%0*i%-s\n", 'm', -1, -475534425, NULL);
	j = ft_printf("ft_printf : cjk7z9IfU0%-5cg8DsSS%0*i%-s\n", 'm', -1, -475534425, NULL);
	printf("i = %d, j = %d\n", i, j);

}