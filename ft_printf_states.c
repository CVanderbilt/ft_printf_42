/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_states.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:11:09 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/31 14:21:35 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_print_options(t_data *data)
{
	char const	*str;
	int			i;

	str = data->str;
	i = data->pos;
	if (str[i] == 'c')
		return (ft_print_chr(data));
	else if (str[i] == 's')
		return (ft_print_str(data));
	else if (ft_in_set("di", str[i]))
		return (ft_print_int(data));
	else if (ft_in_set("uxXpo", str[i]))
		return (ft_print_uns(data));
	else if (str[i] == 'n')
		return (ft_print_num(data));
	else if (str[i] == '%')
		return (ft_print_ptg(data));
	else
		return (str[i] == 0 ? 1 : ft_print_err(data));
}

int		ft_state_print(t_data *data)
{
	char	const *str;

	str = data->str;
	while (ft_in_set("lh", str[data->pos]))
	{
		if (str[data->pos] == 'l')
			data->l_flag++;
		else
			data->h_flag++;
		data->pos++;
	}
	if (data->precision >= 0)
		data->zero_flag = 0;
	return (ft_print_options(data));
}

int		ft_state_precision(t_data *data)
{
	int			i;
	const char	*str;

	i = data->pos;
	str = data->str;
	if (str[i] != '.')
		return (str[i] == 0 ? 1 : 0);
	data->precision = 0;
	i++;
	if (str[i] == '*')
	{
		data->precision = va_arg(g_args, int);
		i++;
	}
	else
	{
		data->precision = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			i++;
	}
	data->pos = i;
	return (str[i] == 0 ? 1 : ft_state_print(data));
}

int		ft_state_width(t_data *data)
{
	int			i;
	const char	*str;

	i = data->pos;
	str = data->str;
	if (str[i] == '*')
	{
		data->width = va_arg(g_args, int);
		i++;
	}
	else if (ft_isdigit(str[i]))
	{
		data->width = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			i++;
	}
	else
		return (str[i] == 0 ? 1 : 0);
	data->pos = i;
	if (str[i] == '.')
		return (ft_state_precision(data));
	return (ft_state_print(data));
}

int		ft_state_flags(t_data *data)
{
	int			i;
	const char	*str;
	char		*set;

	set = data->set_flags;
	str = data->str;
	i = data->pos;
	if (!ft_active_flag(data, str[i]))
	{
		if (str[i] == '.')
			return (ft_state_precision(data));
		if (str[i] == '*' || ft_isdigit(str[i]))
			return (ft_state_width(data));
		return (str[i] == 0 ? 1 : ft_state_print(data));
	}
	data->pos++;
	return (ft_state_flags(data));
}
