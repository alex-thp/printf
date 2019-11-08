/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:38:30 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/08 17:33:30 by ade-temm         ###   ########.fr       */
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
	if (tab->str[tab->index + i] == 'd' || tab->str[tab->index + i] == 'i')
		ft_do_int(va_arg(tab->ap, int), tab);
	if (tab->str[tab->index + i] == 'x' || tab->str[tab->index + i] == 'X')
		ft_do_hexa(va_arg(tab->ap, unsigned int), tab, tab->str[tab->index + i]);
	if (tab->str[tab->index + i] == 'p')
		ft_do_address(va_arg(tab->ap, unsigned long), tab, 0);
	if (tab->str[tab->index + i] == 'c')
		ft_do_char(va_arg(tab->ap, int), tab);
	if (tab->str[tab->index + i] == 's')
		ft_do_string(va_arg(tab->ap, char*), tab);
	if (tab->str[tab->index + i] == 'u')
		ft_do_unsigned_int(va_arg(tab->ap, unsigned int), tab);
	if (tab->str[tab->index + i] == '%')
	{
		ft_putchar_fd('%', 1);
		tab->count +=1;
	}
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
			while (is_set(str[tab->index + i]) == -1)
				i++;
			ft_parse_flags(tab, i);
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

	i = 0;
	i++;
	i = ft_printf("Salut, j'ai %d amis et %c%s tomates %%\nVoici l'adresse du pointeur de i : %p\nEt maintenant ABC en hexa(min) : %x\nEt en maj : %X", 2, 't', "rois", &i, 0xabc, 0xabc);
	printf("\n%d", i);
}