/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:22:43 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/16 18:19:36 by ade-temm         ###   ########.fr       */
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

void	print_spaces(t_list *tab)
{
	int i;
	int size;

	i = 0;
	size = ft_count(tab);
	if (tab->var_int < 0 && tab->val_point > size)
		i++;
	if (size > tab->val_point)
	{
		while (i < tab->val_moins - size)
		{
			ft_putchar_fd(' ', 1);
			i++;
			tab->count += 1;
		}
	}
	else
	{
		while (i < tab->val_moins - tab->val_point)
		{
			ft_putchar_fd(' ', 1);
			i++;
			tab->count += 1;
		}
	}
}

void	print_spaces_hexa(t_list *tab)
{
	int i;
	int size;

	i = 0;
	size = ft_count(tab);
	if (tab->var_ulong < 0 && tab->val_point > size)
		i += 1;
	if (size > tab->val_point)
	{
		while (i < tab->val_moins - size)
		{
			ft_putchar_fd(' ', 1);
			i++;
			tab->count += 1;
		}
	}
	else
	{
		while (i < tab->val_moins - tab->val_point)
		{
			ft_putchar_fd(' ', 1);
			i++;
			tab->count += 1;
		}
	}
}

void	print_spaces_string(t_list *tab)
{
	int		i;
	int		size;

	i = 0;
	size = ft_count(tab);
	if (size > tab->val_point && tab->point == 1)
	{
		while (i < tab->val_moins - tab->val_point)
		{
			ft_putchar_fd(' ', 1);
			i++;
			tab->count += 1;
		}
	}
	else
	{
		while (i < tab->val_moins - size)
		{
			ft_putchar_fd(' ', 1);
			i++;
			tab->count += 1;
		}
	}
}

void	print_zero(t_list *tab)
{
	int		i;
	int		size;

	i = 0;
	size = ft_count(tab);
	if (size > tab->val_point)
	{
		while (i < tab->val_moins - size)
		{
			ft_putchar_fd('0', 1);
			i++;
			tab->count += 1;
		}
	}
	else
	{
		while (i < tab->val_point - tab->val_moins)
		{
			ft_putchar_fd('0', 1);
			i++;
			tab->count += 1;
		}
	}
}

void	print_precision(t_list *tab)
{
	int		size;
	int		i;

	i = 0;
	size = ft_count(tab);
	while (i < tab->val_point - size)
	{
		ft_putchar_fd('0', 1);
		i++;
		tab->count += 1;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_length(long long int nb, int base, t_list *tab)
{
	int		i;

	i = 1;
	if (tab->point == 1 && tab->val_point == 0 && tab->var_int == 0)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > base - 1)
	{
		i++;
		nb /= base;
	}
	return (i);
}

int		ft_length_hexa(unsigned long nb, int base, t_list *tab)
{
	int		i;

	i = 1;
	if (tab->point == 1 && tab->val_point == 0 && tab->var_ulong == 0)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > (unsigned long int)base - 1)
	{
		i++;
		nb /= base;
	}
	return (i);
}

int		ft_count(t_list *tab)
{
	if (tab->arg == 's')
	{
		if (tab->var_string == NULL)
			return (6);
		return (ft_strlen(tab->var_string));
	}
	else if (tab->arg == 'd' || tab->arg == 'i')
		return (ft_length(tab->var_int, 10, tab));
	else if (tab->arg == 'p')
		return (ft_length(tab->var_ulong, 16, tab) + 2);
	else if (tab->arg == 'x' || tab->arg == 'X')
		return (ft_length_hexa(tab->var_ulong, 16, tab));
	else if (tab->arg == 'u')
		return (ft_length(tab->var_ulong, 10, tab));
	else
		return (1);
}

void	ft_redirect(t_list *tab)
{
	if (tab->point == 1)
		tab->zero = 0;
	if (tab->arg == 'd' || tab->arg == 'i')
		ft_make_int(tab);
	else if (tab->arg == 'c')
		ft_make_char(tab);
	else if (tab->arg == 'p')
		ft_make_address(tab);
	else if (tab->arg == 'x' || tab->arg == 'X')
		ft_make_hexa(tab);
	else if (tab->arg == 'u')
		ft_make_unsigned(tab);
	else if (tab->arg == 's')
		ft_make_string(tab);
	else if (tab->arg == '%')
		ft_make_pourcent(tab);
}

void	value(t_list *tab)
{
	if (tab->val_point < 0)
		tab->point = 0;
	if (tab->arg == 'x' || tab->arg == 'X'
	|| tab->arg == 'u')
		tab->var_ulong = va_arg(tab->ap, unsigned int);
	if (tab->arg == 'p')
	{
		tab->var_string = va_arg(tab->ap, char*);
		tab->var_ulong = (unsigned long)tab->var_string;
	}
	if (tab->arg == 'd' || tab->arg == 'i' || tab->arg == 'c')
		tab->var_int = va_arg(tab->ap, int);
	if (tab->arg == 's')
	{
		tab->var_string = va_arg(tab->ap, char*);
		if (tab->var_string == NULL)
			tab->var_string = "(null)\0";
	}
	if (tab->val_point < 0)
	{
		tab->point = 0;
		tab->val_point = 0;
	}
	ft_redirect(tab);
}

void	parse_point(t_list *tab)
{
	int		j;

	j = 1;
	while (is_set(tab->str[tab->index + j]) == -1)
	{
		if (tab->str[tab->index + j] == '.')
		{
			tab->point = 1;
			if (tab->str[tab->index + j + 1] == '*')
				tab->val_point = va_arg(tab->ap, int);
			else if (tab->str[tab->index + j + 1] != '-')
				tab->val_point = ft_atoi(&(tab->str[tab->index + j + 1]));
			while (tab->str[tab->index + j + 1] == '-')
			{
				if (tab->str[tab->index + j + 2] == '*')
					tab->val_point = va_arg(tab->ap, int);
				else
					tab->val_point = ft_atoi(&(tab->str[tab->index + j]));
				j++;
			}
		}
		j++;
	}
	value(tab);
}

void	parse_moins(t_list *tab)
{
	if (tab->str[tab->index + 1] == '-' || tab->str[tab->index + 1] == '*' || tab->str[tab->index + 1] == '0')
	{
		if (tab->str[tab->index + 1] == '*')
			tab->val_moins = va_arg(tab->ap, int);
		else
		{
			if (tab->str[tab->index + 2] == '*')
			{
				tab->val_moins = va_arg(tab->ap, int);
				tab->moins = 1;
			}
			else
				tab->val_moins = ft_atoi(&(tab->str[tab->index + 1]));
		}
	}
	else
		tab->val_moins = ft_atoi(&(tab->str[tab->index + 1]));
	if (tab->val_moins < 0)
	{
		tab->val_moins *= -1;
		tab->moins = 1;
	}
	parse_point(tab);
}

void	parse_zero(t_list *tab)
{
	if (tab->str[tab->index + 1] == '0')
		tab->zero = 1;
	parse_moins(tab);
}