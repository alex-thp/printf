/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:38:30 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/08 17:55:14 by ade-temm         ###   ########.fr       */
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

void	ft_parse_flags(t_list *tab, int i)
{
	int			j;
	long int	arg;

	j = 0;
	arg = 0;
	while (j < i) // Dans cette boucle je dois gérer tous mes flags
	{
		if (tab->str[tab->index + j] == '*')
		{
			arg = va_arg(tab->ap, long int);
		}
		j++;
	}
	ft_do(tab, i);
}

/* Flags : "-0.*"
1) -
2) 0
3) .
4) *
*/
