/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:56:09 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/12 21:14:33 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# include <stdio.h>

typedef struct	s_list
{
	const char			*str;
	va_list				ap;
	int					count;
	int					index;
	char				arg;
	int					moins;
	int					point;
	int					zero;
	int					star;
	unsigned long int	var_ulong;
	int					var_int;
	char				*var_string;
	int					precision;
}						t_list;

int						ft_printf(const char *str, ...);
void					ft_putchar_fd(char c, int fd);
void					ft_do(t_list *tab, int i);
int						is_set(char c);
t_list					*init_tab(const char *str);
void					ft_parse_flags(t_list *tab, int i);
void					ft_do(t_list *tab, int i);
void					ft_do_int(int nb, t_list *tab);
void					ft_do_char(int c, t_list *tab);
void					ft_do_string(char *str, t_list *tab);
void					ft_do_unsigned_int(unsigned int nb, t_list *tab);
void					ft_do_hexa(unsigned int nb, t_list *tab, char c);
void					ft_do_address(unsigned long i, t_list *tab, int j);
int						ft_atoi(const char *str);
void					ft_parse(t_list *tab);
void					ft_parse_2(t_list *tab);
void					ft_parse_3(t_list *tab);
char    				*ft_strdup(char *src);
int						ft_strlen(char *str);

#endif
