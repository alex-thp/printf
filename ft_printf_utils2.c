/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:38:30 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/13 17:19:35 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *str)
{
	int		result;
	int		i;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

void	print_spaces(int nb, t_list *tab)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd(' ', 1);
		i++;
		tab->count += 1;
	}
}

void	print_zero(int nb, t_list *tab)
{
	int i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd('0', 1);
		i++;
		tab->count += 1;
	}
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_length(long long int nb, int base)
{
	int		i;

	i = 1;
	if (nb < 0)
		nb = -nb;
	while (nb > 9)
	{
		i++;
		nb /= base;
	}
	return (i);
}

int		ft_count(t_list *tab)
{
	int		count;

	if (tab->arg == 's')
		return (ft_strlen(tab->var_string));
	else if (tab->arg == 'd' || tab->arg == 'i')
		return (ft_length(tab->var_int, 10));
	else if (tab->arg == 'p')
		return (ft_length(tab->var_ulong, 16) + 2);
	else if (tab->arg == 'x' || tab->arg == 'X')
		return (ft_length(tab->var_ulong, 16));
	else
		return (1);
}

void	ft_make_char(t_list *tab)
{
	print_spaces(tab->val_moins, tab);
	ft_do_char(tab->var_int, tab);
}

void	ft_make_int(t_list *tab)
{
	int		size;
	int		stack;
	int		i;

	size = ft_count(tab);
	i = 1;
	if (tab->moins == 0 && tab->zero == 0)
	{
		if (tab->precision >= size)
			print_spaces(tab->val_moins - tab->precision, tab);
		else
			print_spaces(tab->val_moins - size + 1, tab);
	}
	else if (tab->moins == 0 && tab->zero == 1)
	{
		if (tab->point == 1)
			if (tab->precision >= size)
				print_spaces(tab->val_moins - tab->precision, tab);
			else
				print_spaces(tab->val_moins - size + 1, tab);
		else
		{
			if (tab->precision >= size)
				print_zero(tab->val_moins - tab->precision, tab);
			else
				print_zero(tab->val_moins - size + 1, tab);
		}
	}
	if (tab->point == 1)
	{
		if (tab->var_int < 0)
		{
			tab->var_int *= -1;
			ft_do_char('-', tab);
		}
		print_zero(tab->precision - size, tab);
	}
	ft_do(tab, tab->arg);
	if (tab->moins == 1)
	{
		if (tab->point == 1 && tab->precision >= size)
			print_spaces(tab->val_moins - tab->precision, tab);
		else
			print_spaces(tab->val_moins - size + 1, tab);
	}
}

void	ft_make_string(t_list *tab)
{
	int		spaces;
	int		size;
	char	*res;

	spaces = 0;
	size = ft_count(tab);
	res = 0;
	if (tab->moins == 0)
	{
		spaces = ft_atoi(&(tab->str[tab->index + 1]));
		if (tab->precision <= size)
			print_spaces(spaces - tab->precision, tab);
		else
			print_spaces(spaces - size, tab);
	}
	spaces = 0;
	res = ft_strdup(tab->var_string);
	if (tab->point == 1)
		res[tab->precision] = '\0';
	ft_do_string(res, tab);
	free(res);
	if (tab->moins == 1)
	{
		spaces = ft_atoi(&(tab->str[tab->index + 2]));
		if (tab->precision <= size)
			print_spaces(spaces - tab->precision, tab);
		else
			print_spaces(spaces - size, tab);
	}
}

void	ft_parse(t_list *tab)
{
	int		j;

	j = 1;
	while (tab->str[tab->index + j] != tab->arg)
	{
		if (j == 1)
			tab->val_moins = ft_atoi(&(tab->str[tab->index + 1]));
		if (tab->str[tab->index + 1] == '0')
			tab->zero = 1;
		if (tab->str[tab->index + j] == '-')
			tab->moins = 1;
		if (tab->str[tab->index + j] == '.')
		{
			tab->precision = ft_atoi(&(tab->str[tab->index + j + 1]));
			tab->point = 1;
		}
		j++;
	}
	ft_next_parse(tab);
}

void	ft_next_parse(t_list *tab)
{
	int j;

	j = 1;
	while (tab->str[tab->index + j] != tab->arg)
	{
		if (tab->str[tab->index + j] == '*')
		{
			if (tab->str[tab->index + j - 1] == '.')
				tab->precision = va_arg(tab->ap, int);
			else
				tab->val_moins = va_arg(tab->ap, int);
		}
		j++;
	}
	if (tab->val_moins < 0)
	{
		tab->val_moins *= -1;
		tab->moins = 1;
	}
	ft_parse_2(tab);
}

void	ft_parse_2(t_list *tab)
{
	if (tab->arg == 'x' || tab->arg == 'X'
	|| tab->arg == 'p' || tab->arg == 'u')
		tab->var_ulong = va_arg(tab->ap, unsigned long int);
	if (tab->arg == 'd' || tab->arg == 'i' || tab->arg == 'c')
	{
		tab->var_int = va_arg(tab->ap, int);
		if (tab->var_int < 0 && tab->point == 1)
			tab->val_moins -= 1;
		if (tab->var_int < 0 && tab->point == 1 && tab->precision == 0)
			tab->val_moins -= 1;
	}
	if (tab->arg == 's')
		tab->var_string = va_arg(tab->ap, char*);
	ft_parse_3(tab);
}

void	ft_parse_3(t_list *tab)
{
	if (tab->arg == 'c')
		ft_make_char(tab);
	else if (tab->arg == 's')
		ft_make_string(tab);
	else
		ft_make_int(tab);
}