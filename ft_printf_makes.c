/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_makes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:41:30 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/15 21:02:09 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_make_int(t_list *tab)
{
	int		size;

	size = ft_count(tab);
	if (tab->moins == 0 && tab->zero == 0)
		print_spaces(tab);
	if (tab->moins == 0 && tab->zero == 1)
		print_zero(tab);
	if (tab->point == 1)
	{
		if (tab->var_int < 0)
		{
			tab->var_int *= -1;
			ft_do_char('-', tab);
		}
		print_precision(tab);
	}
	ft_do(tab);
	if (tab->moins == 1)
		print_spaces(tab);
}

void	ft_make_char(t_list *tab)
{
	if (tab->zero == 0 && tab->moins == 0)
		print_spaces(tab);
	if (tab->zero == 1 && tab->moins == 0)
		print_zero(tab);
	ft_do(tab);
	if (tab->moins == 1)
		print_spaces(tab);
}

void	ft_make_address(t_list *tab)
{
	if (tab->moins == 0)
		print_spaces(tab);
	ft_do(tab);
	if (tab->moins == 1)
		print_spaces(tab);
}

void	ft_make_hexa(t_list *tab)
{
	int		size;

	size = ft_count(tab);
	if (tab->moins == 0 && tab->zero == 0)
		print_spaces_hexa(tab);
	if (tab->moins == 0 && tab->zero == 1)
		print_zero(tab);
	if (tab->point == 1)
	{
		if (tab->var_ulong < 0)
		{
			tab->var_ulong *= -1;
			ft_do_char('-', tab);
		}
		print_precision(tab);
	}
	ft_do(tab);
	if (tab->moins == 1)
		print_spaces_hexa(tab);
}

void	ft_make_string(t_list *tab)
{
	int		size;

	size = ft_count(tab);
	if (tab->moins == 0)
		print_spaces_string(tab);
	if (tab->point == 1)
	{
		if (tab->val_point < size)
		{
			write(1, tab->var_string, tab->val_point);
			tab->count += tab->val_point;
		}
		else
			ft_do(tab);
	}
	else
		ft_do(tab);
	if (tab->moins == 1)
		print_spaces_string(tab);
}

void	ft_make_pourcent(t_list *tab)
{
	if (tab->moins == 0 && tab->zero == 0)
		print_spaces(tab);
	if (tab->moins == 0 && tab->zero == 1)
		print_zero(tab);
	ft_do_pourcent(tab);
	if (tab->moins == 1)
		print_spaces(tab);
}

void	ft_make_unsigned(t_list *tab)
{
	int		size;

	size = ft_count(tab);
	if (tab->moins == 0 && tab->zero == 0)
		print_spaces(tab);
	if (tab->moins == 0 && tab->zero == 1)
		print_zero(tab);
	if (tab->point == 1)
		print_precision(tab);
	ft_do(tab);
	if (tab->moins == 1)
		print_spaces(tab);
}
