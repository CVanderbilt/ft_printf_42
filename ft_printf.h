/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:30:26 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:43:50 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

va_list				g_args;

typedef unsigned long long	t_ull;

typedef struct				s_data
{
	int						pos;
	int						size;
	int						width;
	int						precision;
	int						minus_flag;
	int						zero_flag;
	int						plus_flag;
	int						l_flag;
	int						h_flag;
	int						blank_flag;
	int						hash_flag;
	char					actual_type;
	const char				*str;
	char					*out;
	char					*set_flags;
	char					*set_types;
}							t_data;

int							ft_printf(const char *str, ...);

int							ft_print_options(t_data *data);
int							ft_state_print(t_data *data);
int							ft_state_precision(t_data *data);
int							ft_state_width(t_data *data);
int							ft_state_flags(t_data *data);

char						*ft_width_str(t_data *data, char *str);
int							ft_print_str(t_data *data);
int							ft_print_chr(t_data *data);

int							ft_print_int(t_data *data);
char						*ft_print_int_aux(t_data *data, char **tab_aux);
char						*ft_print_int_aux2(t_data *data, char **tab_aux);
char						*ft_print_int_aux3(t_data *data);

char						*ft_width_int(t_data *data, char *str);
char						*ft_precision_int(t_data *data, char *str);
char						*ft_check_sign(char *str);

t_ull						ft_mod_size_uns(t_data *data, t_ull n);
char						*ft_translate(t_ull n, char type);
char						*ft_print_uns_aux(t_data *data);
int							ft_print_uns(t_data *data);

char						*ft_check_prefix(t_data *d, char *s, char *p);
char						*ft_check_prefix_mod(char *str);
char						*ft_prefix_select(t_data *d, char t, t_ull	n);

int							ft_print_ptg(t_data *data);
int							ft_print_num(t_data *data);
int							ft_print_err(t_data *data);
int							ft_active_flag(t_data *data, char flag);

int							ft_save_chr(t_data *data, char c);
int							ft_save(t_data *data, char *tab, int size);
void						ft_data_init(t_data *data, const char *str);
void						ft_reinit_data(t_data *data);
void						ft_free_data(t_data *data);

#endif
