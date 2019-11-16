/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:56:09 by ade-temm          #+#    #+#             */
/*   Updated: 2019/11/16 17:33:29 by ade-temm         ###   ########.fr       */
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
	int					val_moins;
	int					val_point;
}						t_list;

int						ft_printf(const char *str, ...);
void					ft_putchar_fd(char c, int fd);
int						is_set(char c);
t_list					*init_tab(const char *str);
void					ft_parse_flags(t_list *tab, int i);
void					ft_do(t_list *tab);
void					ft_do_int(int nb, t_list *tab);
void					ft_do_char(int c, t_list *tab);
void					ft_do_string(char *str, t_list *tab);
void					ft_do_unsigned_int(unsigned int nb, t_list *tab);
void					ft_do_hexa(unsigned int nb, t_list *tab, char c);
void					ft_do_address(unsigned long i, t_list *tab, int j);
void					ft_do_pourcent(t_list *tab);
int						ft_atoi(const char *str);
char					*ft_strdup(const char *s1);
size_t					ft_strlen(const char *s);
void					parse_moins(t_list *tab);
void					parse_point(t_list *tab);
void					ft_redirect(t_list *tab);
void					parse_zero(t_list *tab);
void					print_spaces(t_list *tab);
void					print_spaces_hexa(t_list *tab);
void					print_spaces_string(t_list *tab);
void					print_zero(t_list *tab);
int						ft_count(t_list *tab);
void					ft_make_int(t_list *tab);
void					ft_make_char(t_list *tab);
void					ft_make_address(t_list *tab);
void					ft_make_string(t_list *tab);
void					ft_make_pourcent(t_list *tab);
void					print_precision(t_list *tab);
void					ft_make_hexa(t_list *tab);
int						ft_length_hexa(unsigned long nb, int base, t_list *tab);
int						ft_length(long long int nb, int base, t_list *tab);
void					value(t_list *tab);
void					ft_make_unsigned(t_list *tab);

#endif
