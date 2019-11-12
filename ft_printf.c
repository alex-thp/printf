/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:38:30 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/12 21:23:33 by alexandre        ###   ########.fr       */
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

	tab = (t_list*)malloc(sizeof(t_list)); //Free à la fin
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

void	ft_do(t_list *tab, int i)
{
	if (tab->arg == 'd' || tab->arg == 'i')
		ft_do_int(tab->var_int, tab);
	if (tab->arg == 'x' || tab->arg == 'X')
		ft_do_hexa(tab->var_ulong, tab, tab->arg);
	if (tab->arg == 'p')
		ft_do_address(tab->var_ulong, tab, 0);
	if (tab->arg == 'c')
		ft_do_char(tab->var_int, tab);
	if (tab->arg == 's')
		ft_do_string(tab->var_string, tab);
	if (tab->arg == 'u')
		ft_do_unsigned_int(tab->var_ulong, tab);
	if (tab->arg == '%')
	{
		ft_putchar_fd('%', 1);
		tab->count +=1;
	}
}

void	ft_init_parse(t_list *tab)
{
	tab->moins = 0;
	tab->point = 0;
	tab->zero = 0;
	tab->star = 0;
	tab->precision = 0;
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
			ft_parse(tab);
			tab->index += i;
		}
		else 
		{
			ft_putchar_fd(str[tab->index], 1);
			tab->count += 1;
		}
		tab->index += 1;
	}
	return (tab->count);
}

#include <stdio.h>

int		main(void)
{
	int i;
	int j;

	i = ft_printf("Salut, j'ai %d amis et %c%-5.2s tomates %%\nVoici l'adresse du pointeur de i : %p\nEt maintenant ABC en hexa(min) : %012.1x\nEt en maj : %X\n\n", 2, 't', "rois", &i, 200, 200);
	j = printf("Salut, j'ai %d amis et %c%-5.2s tomates %%\nVoici l'adresse du pointeur de i : %p\nEt maintenant ABC en hexa(min) : %012.1x\nEt en maj : %X\n\n", 2, 't', "rois", &i, 200, 200);
	//printf("Salut %ces %8.5s", 'l', "amis");
	printf("\n%d", i);
	printf("\n%d", j);
}